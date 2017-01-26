#include <unistd.h>
#include "exec.h"
#include "errors.h"
#include "ast.h"
#include "array_42.h"

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

static int	exec_last_child(const t_ast_node *node, const t_pipe left)
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

static int	exec_child(const t_ast_node *node, t_pipe left)
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

static pid_t	exec_pipe_leader(t_pipe *left, const t_ast_node *leader)
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

/*
 * Créer un process group
 * Assigner chaque child au process group
 * wait la fin du process group
 * retourne l'exit status pour utilisation par les autres tree_walker
 */

static int exec_pipe_sequence(const t_ast_node *node)
{
	t_array		stack;
	t_ast_node	*child;
	t_pipe 		left;
	pid_t		pgid;
	int			exit_status;

	// self set process group leader
	// setpgid(0, 0); // tester le retour
	stack = gather_piped_children(node);
	array_pop(&stack, &child);
	pgid = exec_pipe_leader(&left, child);
	while (stack.len > 1)
	{
		array_pop(&stack, &child);
		left.read = exec_child(child, left);
		if (left.read == -1)
			return (-1);
	}
	if (exec_last_child(node, left) == -1)
		return (-1);

	// Creation du process group
	// Election de l'ainee comme process group leader
	// Envoie du pgid a tous les autres enfants, qui doivent s'y deplacer

	// Wait du pgid de la pipe sequence
	// Wait until [ECHILD]
	// Dans les autres cas d'erreurs, ce sont des vraies erreurs attention

	return (exit_status);
}
// while ((pid = waitpid()) != -1)
// {
// 	if pid == last_child_pid
// 		ret = exit_status_last_child
// }

int	exec_node_pipe(const t_ast_node *node)
{
	int	pgid;

	pgid = fork();
	if (pgid == -1)
		error_set_context("fork: %s", strerror(errno));
	else if (pgid == 0)
	{
		exec_node_pipe(node);
	}
//  set process group leader
//	waitpid(pid); // On attend le fork de controle
}

// exec_pipe_command -> (launch builtin + exit after builtin completion)
//                   -> (launch binary)
