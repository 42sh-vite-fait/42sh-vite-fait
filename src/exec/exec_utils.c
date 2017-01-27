#include <assert.h>
#include "array_42.h"
#include "exec.h"

int	wait_for_children(pid_t last_pid, pid_t pgid)
{
	pid_t		pid;
	int			status;
	int			ret;

	ret = -1;
	while ((pid = waitpid(pgid, &status, 0)) != -1)
	{
		if (pid == last_pid)
			ret = get_exit_status(status);
	}
	return (ret);
}

t_array gather_nodes(const t_ast_node *node, bool (*pred)(int node_type))
{
	t_array	stack;

	assert(node != NULL);
	assert(pred != NULL);
	fatal_malloc(array_init(&stack, sizeof(t_ast_node*)));
	while ((*pred)(node->type))
	{
		fatal_malloc(array_push(&stack, &node->right));
		node = node->left;
	}
	array_push(&stack, &node);
	return (stack);
}
