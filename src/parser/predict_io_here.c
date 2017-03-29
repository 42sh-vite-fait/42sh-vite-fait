#include "parser.h"

bool	check_requirements_io_here(const t_parser *parser)
{
	if (parser_check_current_token_type(parser, E_TOKEN_DLESS))
		return (true);
	return (false);
}

/*
** io_here : DLESS     here_end
*/

int		predict_io_here(t_parser *parser, struct s_redirection *redir)
{
	if (check_requirements_io_here(parser) == false)
		return (ERROR_);
	parser_consume_token(parser);
	if (!parser_check_current_token_type(parser, E_TOKEN_WORD))
		return (ERROR_);
	parser_consume_token(parser);
	parser_heredoc_push(parser, redir);
	return (OK_);
}
