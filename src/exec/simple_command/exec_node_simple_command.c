/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node_simple_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:01:48 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:01:55 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "ast.h"
#include "exec.h"
#include "builtins.h"

extern t_tree_walker	*const g_walkers[];

int	exec_node_simple_command(const t_ast_node *node, const t_string *input)
{
	t_token	*token;
	int		ret;

	assert(node != NULL);
	if (node->command.words.len == 0)
		return (exec_simple_command_binary(node->command, input));
	token = *(t_token**)array_get_first(&node->command.words);
	if (is_builtin(input->str + token->start, token->len))
		ret = exec_simple_command_builtin(node->command, input);
	else
		ret = exec_simple_command_binary(node->command, input);
	return (ret);
}
