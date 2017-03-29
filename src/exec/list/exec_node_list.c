#include <assert.h>
#include "exec.h"
#include "ast.h"

extern t_tree_walker	*const g_walkers[];

int		exec_node_list(const t_ast_node *node, const t_string *input)
{
	t_array	list_nodes_stack;
	int		ret;

	assert(node != NULL);
	list_nodes_stack = gather_childrens_nodes(node, E_AST_LIST);
	array_pop(&list_nodes_stack, &node);
	ret = g_walkers[node->type](node, input);
	while (list_nodes_stack.len > 0)
	{
		array_pop(&list_nodes_stack, &node);
		ret = g_walkers[node->type](node, input);
	}
	array_shutdown(&list_nodes_stack);
	return (ret);
}
