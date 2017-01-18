#include "parser.h"

bool	check_requirements_compound_list(const t_parser *parser)
{
	if (check_requirements_linebreak(parser))
		return (true);
	return (false);
}

/*
** compound_list : linebreak term
**               | linebreak term separator
*/

int		predict_compound_list(t_parser *parser, t_ast_node **from_parent)
{
	if (predict_linebreak(parser) != PARSER_NO_ERROR)
		return (ERR_PARSING);
	if (predict_term(parser, from_parent) != PARSER_NO_ERROR)
		return (ERR_PARSING);
	if (check_requirements_separator(parser))
		return (predict_separator(parser));
	return (PARSER_NO_ERROR);
}
