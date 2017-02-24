#include <assert.h>
#include "ast.h"
#include "exec.h"
#include "array_42.h"
#include "errors.h"

#define SELF_PGID	0

/*
** stdin -> pipe, read end
*/

static int	exec_last_child(const t_ast_node *node, int left_read)
{
	pid_t	child;

	assert(node != NULL);
	child = -1;
	if (exec_fork(&child) != NO_ERROR)
		pipe_kill_pipe_sequence();
	if (child == 0)
	{
		if (pipe_replace_stdin(left_read) == NO_ERROR)
			exec_pipe_command(node->command);
		pipe_kill_pipe_sequence();
	}
	else
	{
		if (exec_close_fd(left_read) != NO_ERROR)
			pipe_kill_pipe_sequence();
	}
	return (child);
}

/*
** stdin -> pipe, read end
** stdout -> pipe, write end
*/

static int	exec_middle_child(const t_ast_node *node, int left_read)
{
	t_pipe 	right;
	pid_t	child;

	assert(node != NULL);
	child = -1;
	if (pipe_init(&right) != NO_ERROR || exec_fork(&child) != NO_ERROR)
		pipe_kill_pipe_sequence();
	if (child == 0)
	{
		if (pipe_replace_stdin(left_read) == NO_ERROR
				&& pipe_replace_stdout(right.write) == NO_ERROR
				&& exec_close_fd(right.read) == NO_ERROR)
			exec_pipe_command(node->command);
		pipe_kill_pipe_sequence();
	}
	else
	{
		if (exec_close_fd(right.write) != NO_ERROR
				|| exec_close_fd(left_read) != NO_ERROR)
			pipe_kill_pipe_sequence();
	}
	return (right.read);
}

/*
** stdout -> pipe, write end (right write)
** return the read end of the pipe
*/

static int	exec_first_child(const t_ast_node *node)
{
	t_pipe	right;
	pid_t	child;

	assert(node != NULL);
	child = -1;
	if (pipe_init(&right) != NO_ERROR || exec_fork(&child) != NO_ERROR)
		pipe_kill_pipe_sequence();
	if (child == 0)
	{
		if (pipe_replace_stdout(right.write) == NO_ERROR
				&& exec_close_fd(right.read) == NO_ERROR)
			exec_pipe_command(node->command);
		pipe_kill_pipe_sequence();
	}
	else
	{
		if (exec_close_fd(right.write) != NO_ERROR)
			pipe_kill_pipe_sequence();
	}
	return (right.read);
}

/*
** We are in the _control fork_
*/

void		exec_pipe_sequence(const t_ast_node *node)
{
	t_array	pipe_nodes_stack;
	pid_t	last_pid;
	int		read_end;

	// gather_nodes
	pipe_nodes_stack = gather_nodes(node, E_AST_PIPE_SEQUENCE);

	// first child
	array_pop(&pipe_nodes_stack, &node);
	read_end = exec_first_child(node);

	// middle child(ren)
	while (pipe_nodes_stack.len > 1)
	{
		array_pop(&pipe_nodes_stack, &node);
		read_end = exec_middle_child(node, read_end);
	}

	// last child
	array_pop(&pipe_nodes_stack, &node);
	last_pid = exec_last_child(node, read_end);

	// wait for the last child and return his exit status
	_exit(wait_for_children(last_pid, SELF_PGID));
}
