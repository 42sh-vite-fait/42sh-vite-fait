#include "parser.h"

bool	check_requirements_linebreak(const t_parser *parser)
{
	(void)parser;
	return (true);
}

/*
** linebreak : newline_list
**           | // empty
*/

int		predict_linebreak(t_parser *parser)
{
	if (check_requirements_newline_list(parser))
		predict_newline_list(parser);
	return (PARSER_NO_ERROR);
}
