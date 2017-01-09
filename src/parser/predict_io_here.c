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

int		predict_io_here(t_parser *parser, char **heredoc_filename)
{
	if (check_requirements_io_here(parser) == false)
		return (ERR_PARSING);
	parser_consume_token(parser);
	if (!parser_check_current_token_type(parser, E_TOKEN_WORD))
		return (ERR_PARSING);
	*heredoc_filename = heredoc(parser_get_current_token(parser));
	if (*heredoc_filename == NULL)
		return (ERR_HEREDOC);
	parser_consume_token(parser);
	return (NO_ERROR);
}
