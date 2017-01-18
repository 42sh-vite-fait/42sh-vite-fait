#include "parser.h"

/*
** program : linebreak complete_commands linebreak
**         | linebreak
*/

int	predict_program(t_parser *parser, t_ast_node **root)
{
	if (predict_linebreak(parser) != PARSER_NO_ERROR)
		return (ERR_PARSING);
	if (check_requirements_complete_commands(parser))
	{
		if (predict_complete_commands(parser, root) != PARSER_NO_ERROR)
			return (ERR_PARSING);
		if (predict_linebreak(parser) != PARSER_NO_ERROR)
			return (ERR_PARSING);
	}
	return (PARSER_NO_ERROR);
}
