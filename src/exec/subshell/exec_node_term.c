/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node_term.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:01:48 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:01:58 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "exec.h"
#include "ast.h"

extern t_tree_walker	*const g_walkers[];

int		exec_node_term(const t_ast_node *node, const t_string *input)
{
	t_array	term_nodes_stack;
	int		ret;

	assert(node != NULL);
	term_nodes_stack = gather_childrens_nodes(node, E_AST_TERM);
	array_pop(&term_nodes_stack, &node);
	ret = g_walkers[node->type](node, input);
	while (term_nodes_stack.len > 0)
	{
		array_pop(&term_nodes_stack, &node);
		ret = g_walkers[node->type](node, input);
	}
	return (ret);
}
