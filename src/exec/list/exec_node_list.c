#include <assert.h>
#include "exec.h"

extern t_tree_walker	*const g_walkers[];

int		exec_node_list(const t_ast_node *node)
{
	t_array	list_nodes_stack;
	int		ret;

	assert(node != NULL);
	list_nodes_stack = gather_nodes(node, E_AST_LIST);
	array_pop(&list_nodes_stack, &node);
	ret = g_walkers[node->left->type](node->left);
	while (list_nodes_stack.len > 0)
	{
		array_pop(&list_nodes_stack, &node);
		ret = g_walkers[node->left->type](node->left);
	}
	return (ret);
}
