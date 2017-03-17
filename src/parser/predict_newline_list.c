#include "parser.h"

bool	check_requirements_newline_list(const t_parser *parser)
{
	return (parser_check_current_token_type(parser, E_TOKEN_NEWLINE));
}

/*
** newline_list :              NEWLINE
**              | newline_list NEWLINE
*/

int		predict_newline_list(t_parser *parser)
{
	int	ret;

	ret = ERROR_;
	while (parser_check_current_token_type(parser, E_TOKEN_NEWLINE))
	{
		parser_consume_token(parser);
		ret = OK_;
	}
	return (ret);
}
