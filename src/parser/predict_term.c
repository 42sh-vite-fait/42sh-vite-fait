#include "parser.h"

bool	check_requirements_term(const t_parser *parser)
{
	if (check_requirements_and_or(parser))
		return (true);
	return (false);
}

static bool	check_requirements_ambiguous_sep_rule(const t_parser *parser)
{
	t_parser	parser_copy;

	parser_copy = *parser;
	if (check_requirements_separator(&parser_copy))
	{
		predict_separator(&parser_copy);
		if (check_requirements_and_or(&parser_copy))
			return (true);
	}
	return (false);
}


static int	parse_right_term(t_parser *parser, t_ast_node *node)
{
	node->type = E_AST_TERM;
	node->token = parser_get_current_token(parser);
	if (predict_separator(parser) != PARSER_NO_ERROR)
		return (ERR_PARSING);
	node->right = ast_node_create(&parser->ast);
	if (predict_and_or(parser, &node->right) != PARSER_NO_ERROR)
		return (ERR_PARSING);
	return (PARSER_NO_ERROR);
}

/*
** term : term separator and_or
**      |                and_or
*/

int		predict_term(t_parser *parser, t_ast_node **from_parent)
{
	t_ast_node	*node;

	node = ast_node_create(&parser->ast);
	*from_parent = node;
	if (predict_and_or(parser, &node->left) != PARSER_NO_ERROR)
		return (ERR_PARSING);
	if (check_requirements_ambiguous_sep_rule(parser))
	{
		if (parse_right_term(parser, node) != PARSER_NO_ERROR)
			return (ERR_PARSING);
		while (check_requirements_ambiguous_sep_rule(parser))
		{
			node = ast_node_create(&parser->ast);
			node->left = *from_parent;
			*from_parent = node;
			if (parse_right_term(parser, node) != PARSER_NO_ERROR)
				return (ERR_PARSING);
		}
	}

	return (PARSER_NO_ERROR);
}
