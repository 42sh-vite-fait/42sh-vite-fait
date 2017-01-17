#include "parser.h"

bool	check_requirements_io_here(const t_parser *parser)
{
	if (parser_check_current_token_type(parser, E_TOKEN_DLESS)
			|| parser_check_current_token_type(parser, E_TOKEN_DLESSDASH))
		return (true);
	return (false);
}

/*
** io_here : DLESS     here_end
**         | DLESSDASH here_end
*/

int		predict_io_here(t_parser *parser)
{
	if (check_requirements_io_here(parser))
	{
		parser_consume_token(parser);
		return (parser_consume_if_match(parser, E_TOKEN_WORD));
	}
	return (ERR_PARSING);
}
