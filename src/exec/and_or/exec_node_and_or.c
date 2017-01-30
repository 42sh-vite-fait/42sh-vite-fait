#include <assert.h>
#include "exec.h"

extern t_tree_walker	*const g_walkers[];

static int	conditionnal_exec_and_or(const t_ast_node *node, int prev_ret)
{
	if (node->token->type == E_TOKEN_AND_IF)
	{
		if (prev_ret == 0)
			return (g_walkers[node->right->type](node->right));
	}
	else
	{
		if (prev_ret != 0)
			return (g_walkers[node->right->type](node->right));
	}
	return (prev_ret);
}

int		exec_node_and_or(const t_ast_node *node)
{
	t_array	andor_nodes_stack;
	int		ret;

	assert(node != NULL);
	andor_nodes_stack = gather_nodes(node, E_AST_AND_OR);
	array_pop(&andor_nodes_stack, &node);
	ret = g_walkers[node->left->type](node->left);
	ret = conditionnal_exec_and_or(node, ret);
	while (andor_nodes_stack.len > 0)
	{
		array_pop(&andor_nodes_stack, &node);
		ret = conditionnal_exec_and_or(node, ret);
	}
	return (ret);
}
