#include <assert.h>
#include "exec.h"
#include "ast.h"

extern t_tree_walker	*const g_walkers[];

int		exec_node_subshell(const t_ast_node *node)
{
	pid_t	subshell;
	int		status;

	assert(node != NULL);
	if (exec_fork(&subshell) != NO_ERROR)
		return (-1);
	if (subshell == 0)
	{
		exec_child_set_context();
		signal(SIGTTOU, SIG_IGN); // TODO: solution
		if (exec_redirection(node->command.redirections) != NO_ERROR)
		{
			error_print("execution: subshell");
			_exit(-1);
		}
		_exit(g_walkers[node->left->type](node->left));
	}
	else
		status = exec_parent_wait_child_process_group(subshell);
	return (status);
}
