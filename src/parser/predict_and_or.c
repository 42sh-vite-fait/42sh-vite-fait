#include "parser.h"

bool		check_requirements_and_or(const t_parser *parser)
{
	if (check_requirements_pipe_sequence(parser))
		return (true);
	return (false);
}

static int	parse_right_and_or(t_parser *parser, t_ast_node *node)
{
	node->type = E_AST_AND_OR;
	node->token = parser_get_current_token(parser);
	parser_consume_token(parser);
	if (predict_linebreak(parser) != OK_)
		return (ERROR_);
	if (predict_pipe_sequence(parser, &node->right) != OK_)
		return (ERROR_);
	return (OK_);
}

/*
** and_or :                         pipe_sequence
**        | and_or AND_IF linebreak pipe_sequence
**        | and_or OR_IF  linebreak pipe_sequence
*/

int			predict_and_or(t_parser *parser, t_ast_node **from_parent)
{
	t_ast_node	*node;

	node = ast_node_create(&parser->ast);
	*from_parent = node;
	if (predict_pipe_sequence(parser, &node->left) != OK_)
		return (ERROR_);
	if (parser_check_current_token_type(parser, E_TOKEN_AND_IF)
			|| parser_check_current_token_type(parser, E_TOKEN_OR_IF))
	{
		if (parse_right_and_or(parser, node) != OK_)
			return (ERROR_);
		while (parser_check_current_token_type(parser, E_TOKEN_AND_IF)
				|| parser_check_current_token_type(parser, E_TOKEN_OR_IF))
		{
			node = ast_node_create(&parser->ast);
			node->left = *from_parent;
			*from_parent = node;
			if (parse_right_and_or(parser, node) != OK_)
				return (ERROR_);
		}
	}
	return (OK_);
}
