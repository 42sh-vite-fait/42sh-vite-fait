/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:36:42 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:36:44 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	ast_node_command_init(t_ast_node *node)
{
	t_command	*c;

	c = &node->command;
	if (node->type == E_AST_SUBSHELL)
		fatal_malloc(array_init(&c->redirections,
					sizeof(struct s_redirection)));
	else if (node->type == E_AST_SIMPLE_COMMAND)
	{
		fatal_malloc(array_init(&c->words, sizeof(t_token*)));
		fatal_malloc(array_init(&c->redirections,
					sizeof(struct s_redirection)));
	}
}

void	ast_node_command_shutdown(t_ast_node *node)
{
	if (node->type == E_AST_SIMPLE_COMMAND)
	{
		array_shutdown(&node->command.redirections);
		array_shutdown(&node->command.words);
	}
	else if (node->type == E_AST_SUBSHELL)
	{
		array_shutdown(&node->command.redirections);
	}
}
