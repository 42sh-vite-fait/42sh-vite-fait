#include "parser.h"

bool	check_requirements_subshell(const t_parser *parser)
{
	if (parser_check_current_token_type(parser, E_TOKEN_LPAREN))
		return (true);
	return (false);
}

/*
** subshell : '(' compound_list ')'
*/

int		predict_subshell(t_parser *parser, t_ast_node *self)
{
	self->token = parser_get_current_token(parser);
	self->type = E_AST_SUBSHELL;
	if (parser_consume_if_match(parser, E_TOKEN_LPAREN) != NO_ERROR)
		return (ERR_PARSING);
	if (predict_compound_list(parser, &self->left) != NO_ERROR)
		return (ERR_PARSING);
	if (parser_consume_if_match(parser, E_TOKEN_RPAREN) != NO_ERROR)
		return (ERR_PARSING);
	return (NO_ERROR);
}