#include <assert.h>
#include "exec.h"

#include <stdio.h>
extern t_tree_walker	*const g_walkers[];

int		exec_node_and_or(const t_ast_node *node)
{
	int		ret;

	assert(node != NULL);
	ret = g_walkers[node->left->type](node->left);
	if (node->token->type == E_TOKEN_AND_IF)
	{
		if (ret == 0)
			return (g_walkers[node->right->type](node->right));
	}
	else if (node->token->type == E_TOKEN_OR_IF)
	{
		if (ret != 0)
			return (g_walkers[node->right->type](node->right));
	}
	else
		assert(0);
	return (ret);
}

/* static int	conditionnal_exec_and_or(const t_ast_node *node, int prev_ret) */
/* { */
/* 	if (node->token->type == E_TOKEN_AND_IF) */
/* 	{ */
/* 		if (prev_ret == 0) */
/* 			return (g_walkers[node->right->type](node->right)); */
/* 	} */
/* 	else */
/* 	{ */
/* 		if (prev_ret != 0) */
/* 			return (g_walkers[node->right->type](node->right)); */
/* 	} */
/* 	return (prev_ret); */
/* } */

/* int		exec_node_and_or(const t_ast_node *node) */
/* { */
/* 	t_array	andor_nodes_stack; */
/* 	int		ret; */

/* 	assert(node != NULL); */
/* 	andor_nodes_stack = gather_nodes(node, E_AST_AND_OR); */
/* 	array_pop(&andor_nodes_stack, &node); */
/* 	// Crash: la stack contient les nodes des commandes/pipes, pas les AND_OR */
/* 	// Cette facon fonctionne pour les LIST */
/* 	// Supprimer gather_nodes et utiliser une recursion ? */
/* 	// Ou créer une structure qui contient le node left/right et le type du token */
/* 	ret = g_walkers[node->type](node); */
/* 	array_pop(&andor_nodes_stack, &node); */
/* 	ret = conditionnal_exec_and_or(node, ret); */
/* 	while (andor_nodes_stack.len > 0) */
/* 	{ */
/* 		array_pop(&andor_nodes_stack, &node); */
/* 		ret = conditionnal_exec_and_or(node, ret); */
/* 	} */
/* 	return (ret); */
/* } */
