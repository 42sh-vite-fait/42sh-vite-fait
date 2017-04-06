/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node_complete_command.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:01:48 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:04:21 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "exec.h"
#include "ast.h"

extern t_tree_walker	*const g_walkers[];

int		exec_node_complete_commands(const t_ast_node *node,
		const t_string *input, bool set_context)
{
	t_array	complete_commands_nodes_stack;
	int		ret;

	assert(node != NULL);
	complete_commands_nodes_stack = gather_childrens_nodes(node,
			E_AST_COMPLETE_COMMANDS);
	array_pop(&complete_commands_nodes_stack, &node);
	ret = g_walkers[node->type](node, input, set_context);
	while (complete_commands_nodes_stack.len > 0)
	{
		array_pop(&complete_commands_nodes_stack, &node);
		ret = g_walkers[node->type](node, input, set_context);
	}
	array_shutdown(&complete_commands_nodes_stack);
	return (ret);
}

int		exec_node_complete_command(const t_ast_node *node,
		const t_string *input, bool set_context)
{
	t_array	complete_command_nodes_stack;
	int		ret;

	assert(node != NULL);
	complete_command_nodes_stack = gather_childrens_nodes(node,
			E_AST_COMPLETE_COMMAND);
	array_pop(&complete_command_nodes_stack, &node);
	ret = g_walkers[node->type](node, input, set_context);
	while (complete_command_nodes_stack.len > 0)
	{
		array_pop(&complete_command_nodes_stack, &node);
		ret = g_walkers[node->type](node, input, set_context);
	}
	array_shutdown(&complete_command_nodes_stack);
	return (ret);
}
