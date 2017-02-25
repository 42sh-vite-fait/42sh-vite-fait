#include <assert.h>
#include "exec.h"
#include "ast.h"

extern t_tree_walker	*const g_walkers[];

int		exec_node_term(const t_ast_node *node)
{
	t_array	term_nodes_stack;
	int		ret;

	assert(node != NULL);
	term_nodes_stack = gather_childrens_nodes(node, E_AST_TERM);
	array_pop(&term_nodes_stack, &node);
	ret = g_walkers[node->type](node);
	while (term_nodes_stack.len > 0)
	{
		array_pop(&term_nodes_stack, &node);
		ret = g_walkers[node->type](node);
	}
	return (ret);
}
