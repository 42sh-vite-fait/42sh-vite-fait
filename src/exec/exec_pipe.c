#include <unistd.h>
#include "exec.h"
#include "errors.h"
#include "ast.h"
#include "array_42.h"

static t_array	gather_piped_childs(t_ast_node *node)
{
	t_array	stack;

	fatal_malloc(array_init(&stack, sizeof(*node)));
	while (node->type == E_AST_PIPE_SEQUENCE)
	{
		fatal_malloc(array_push(&stack, &node->right));
		node = node->left;
	}
	array_push(&stack, &node->left);
	return (stack);
}

static pid_t	exec_first_child(t_command command, const t_pipe left)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_set_context("fork: %s", strerror(errno));
	else if (pid == 0)
	{
		close(left.read);
		pipe_replace_stdout(left.write);
		exec_command(command);
	}
	return (pid);
}

static pid_t	exec_last_child(t_command command, const t_pipe right)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_set_context("fork: %s", strerror(errno));
	else if (pid == 0)
	{
		pipe_replace_stdin(right.read);
		exec_command(command);
	}
	return (pid);
}

static pid_t	exec_child(t_command command, const t_pipe left,
		const t_pipe right)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_set_context("fork: %s", strerror(errno));
	else if (pid == 0)
	{
		close(right.read);
		pipe_replace_stdout(right.write);
		pipe_replace_stdin(left.read);
		exec_command(command);
	}
	return (pid);
}

static int	pipe_magic(t_pipe *pipe)
{
	int	p[2];

	if (pipe(p) == -1)
	{
		error_set_context("pipe: %s", strerror(errno));
		return (-1);
	}
	pipe->read = p[0];
	pipe->write = p[1];
	return (0);
}

int exec_pipe(t_ast_node *node)
{
	t_array		stack;
	t_ast_node	*child;
	t_pipe 		left;
	t_pipe 		right;
	pid_t		ret;

	stack = gather_piped_childs(node);
	array_pop(&stack, &child);
	if (pipe_magic(&left) == -1)
		return (-1);
	if ((ret = exec_first_child(node->command, left)) == -1)
		return (-1);
	close(left.write);

	// begin multiple childs
	while (stack.len > 1)
	{
		array_pop(&stack, &child);
		if (pipe_magic(&right) == -1)
			return (-1);
		if ((ret = exec_child(child->command, left_pipe, right_pipe)) == -1)
			return (-1);

		close(left.read);
		close(right.write);
		left.read = right.read;
	}

	// last child
	if ((ret = exec_last_child(node->command, left_pipe)) == -1)
		return (-1);
	close(left_pipe[0]); // read end first pipe
}
