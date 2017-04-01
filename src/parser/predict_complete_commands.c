/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_complete_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:36:32 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:36:33 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool		check_requirements_complete_commands(const t_parser *parser)
{
	if (check_requirements_complete_command(parser))
		return (true);
	return (false);
}

static bool	check_requirements_ambiguous_newline_rule(const t_parser *parser)
{
	t_parser	parser_copy;

	parser_copy = *parser;
	if (check_requirements_newline_list(&parser_copy))
	{
		predict_newline_list(&parser_copy);
		if (check_requirements_complete_command(&parser_copy))
			return (true);
	}
	return (false);
}

static int	parse_right_complete_commands(t_parser *parser, t_ast_node *node)
{
	node->type = E_AST_COMPLETE_COMMANDS;
	node->token = parser_get_current_token(parser);
	if (predict_newline_list(parser) != OK_)
		return (ERROR_);
	if (predict_complete_command(parser, &node->right) != OK_)
		return (ERROR_);
	return (OK_);
}

/*
** complete_commands: complete_commands newline_list complete_command
**                  |                                complete_command
*/

int			predict_complete_commands(t_parser *parser,
		t_ast_node **from_parent)
{
	t_ast_node	*node;

	node = ast_node_create(&parser->ast);
	*from_parent = node;
	if (predict_complete_command(parser, &node->left) != OK_)
		return (ERROR_);
	if (check_requirements_ambiguous_newline_rule(parser))
	{
		if (parse_right_complete_commands(parser, node) != OK_)
			return (ERROR_);
		while (check_requirements_ambiguous_newline_rule(parser))
		{
			node = ast_node_create(&parser->ast);
			node->left = *from_parent;
			*from_parent = node;
			if (parse_right_complete_commands(parser, node) != OK_)
				return (ERROR_);
		}
	}
	return (OK_);
}
