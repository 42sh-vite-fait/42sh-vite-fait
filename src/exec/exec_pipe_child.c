#include "ast.h"
#include "exec.h"
#include "array_42.h"

#define SELF_PGID 0

static t_array	gather_piped_children(const t_ast_node *node)
{
	t_array	stack;

	fatal_malloc(array_init(&stack, sizeof(*node)));
	while (node->type == E_AST_PIPE_SEQUENCE)
	{
		fatal_malloc(array_push(&stack, &node->right));
		node = node->left;
	}
	array_push(&stack, &node);
	return (stack);
}

static int		exec_last_child(const t_ast_node *node, const t_pipe left)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_set_context("fork: %s", strerror(errno));
	else if (pid == 0)
	{
		pipe_replace_stdin(left.read);
		exec_pipe_command(node->command);
	}
	close(left.read);
	return (pid);
}

static int		exec_child(const t_ast_node *node, t_pipe left)
{
	t_pipe 	right;
	pid_t	pid;

	if (pipe_init(&right) == -1)
		return (-1);

	pid = fork();
	if (pid == -1)
		error_set_context("fork: %s", strerror(errno));
	else if (pid == 0)
	{
		close(right.read);
		pipe_replace_stdout(right.write);
		pipe_replace_stdin(left.read);
		exec_pipe_command(node->command);
	}
	close(left.read);
	close(right.write);
	return (pid);
}

static pid_t	exec_first_child(t_pipe *left, const t_ast_node *leader)
{
	pid_t	pid;

	if (pipe_init(left) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		error_set_context("fork: %s", strerror(errno));
	else if (pid == 0)
	{
		close(left->read);
		pipe_replace_stdout(left->write);
		exec_pipe_command(leader->command);
	}
	close(left->write);
	return (pid);
}

int				exec_pipe_sequence(const t_ast_node *node)
{
	t_array		stack;
	t_ast_node	*child;
	t_pipe 		left;
	pid_t		last_pid;

	setpgid(0, 0); // tester le retour
	stack = gather_piped_children(node);
	array_pop(&stack, &child);
	exec_first_child(&left, child); // test retour, d'ailleur c'est meme plus un leader du tout
	while (stack.len > 1)
	{
		array_pop(&stack, &child);
		left.read = exec_child(child, left);
		if (left.read == -1)
			return (-1);
	}
	if ((last_pid = exec_last_child(node, left)) == -1)
		return (-1);
	_exit(wait_for_children(last_pid, SELF_PGID));
	// Gerer les signaux
}
