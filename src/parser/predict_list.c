#include "parser.h"

bool	check_requirements_list(const t_parser *parser)
{
	if (check_requirements_and_or(parser))
		return (true);
	return (false);
}

static bool	check_requirements_ambiguous_sep_rule(const t_parser *parser)
{
	t_parser	parser_copy;

	parser_copy = *parser;
	if (check_requirements_separator_op(&parser_copy))
	{
		parser_consume_token(&parser_copy);
		if (check_requirements_and_or(&parser_copy))
			return (true);
	}
	return (false);
}

static int	parse_right_list(t_parser *parser, t_ast_node *node)
{
	node->type = E_AST_LIST;
	node->token = parser_get_current_token(parser);
	if (predict_separator_op(parser) != OK_)
		return (ERROR_);
	if (predict_and_or(parser, &node->right) != OK_)
		return (ERROR_);
	return (OK_);
}

/*
** list : list separator_op and_or
**      |                   and_or
*/

int		predict_list(t_parser *parser, t_ast_node **from_parent)
{
	t_ast_node	*node;

	node = ast_node_create(&parser->ast);
	*from_parent = node;

	if (predict_and_or(parser, &node->left) != OK_)
		return (ERROR_);

	if (check_requirements_ambiguous_sep_rule(parser))
	{
		if (parse_right_list(parser, node) != OK_)
			return (ERROR_);

		while (check_requirements_ambiguous_sep_rule(parser))
		{
			node = ast_node_create(&parser->ast);
			node->left = *from_parent;
			*from_parent = node;
			if (parse_right_list(parser, node) != OK_)
				return (ERROR_);
		}
	}

	return (OK_);
}
