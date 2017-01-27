#include "ast.h"
#include "exec.h"
#include "array_42.h"
#include "errors.h"

#define SELF_PGID	0

static int	exec_last_child(const t_ast_node *node, pid_t *pid)
{
	t_pipe	left;

	if (pipe_init(&left) != NO_ERROR)
		return (-1);
	if (exec_fork(pid) != NO_ERROR)
		return (-1);
	if (*pid == 0)
	{
		if (pipe_replace_stdin(left.read) != NO_ERROR
				|| exec_close_fd(left.write) != NO_ERROR)
			return (-1);
		exec_pipe_command(node->command);
	}
	if (exec_close_fd(left.read) != NO_ERROR)
		return (-1);
	return (left.write);
}

static int	exec_child(const t_ast_node *node, int right_write)
{
	t_pipe 	left;
	pid_t	pid;

	if (pipe_init(&left) != NO_ERROR)
		return (-1);
	if (exec_fork(&pid) != NO_ERROR)
		return (-1);
	else if (pid == 0)
	{
		if (pipe_replace_stdout(right_write) != NO_ERROR
				|| pipe_replace_stdin(left.read) != NO_ERROR
				|| exec_close_fd(left.write) != NO_ERROR)
			return (-1);
		exec_pipe_command(node->command);
	}
	if (exec_close_fd(left.read) != NO_ERROR
			|| exec_close_fd(right_write) != NO_ERROR)
		return (-1);
	return (left.write);
}

static int	exec_first_child(const t_ast_node *node, int right_write)
{
	pid_t	pid;

	if (exec_fork(&pid) != NO_ERROR)
		return (-1);
	else if (pid == 0)
	{
		pipe_replace_stdout(right_write);
		exec_pipe_command(node->command);
	}
	if (exec_close_fd(right_write) != NO_ERROR)
		return (-1);
	return (NO_ERROR);
}

/*
** Currently in the control fork
*/
void		exec_pipe_sequence(const t_ast_node *node)
{
	pid_t	last_pid;
	int		write_end;

	if (exec_process_group_create(0, 0) != NO_ERROR)
		_exit(EXIT_FAILURE);
	if ((write_end = exec_last_child(node, &last_pid)) == -1)
		pipe_exit_on_child_error();
	node = node->left;
	while (node->type == E_AST_PIPE_SEQUENCE)
	{
		if ((write_end = exec_child(node, write_end)) == -1)
			pipe_exit_on_child_error();
		node = node->left;
	}
	if (exec_first_child(node, write_end) == -1)
		pipe_exit_on_child_error();

	/* _exit(wait_for_children(last_pid, SELF_PGID)); */
}
// TODO: Gerer les signaux
