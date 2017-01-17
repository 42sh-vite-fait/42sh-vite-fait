#include "parser.h"

bool	check_requirements_cmd_suffix(const t_parser *parser)
{
	if (check_requirements_io_redirect(parser)
			|| parser_check_current_token_type(parser, E_TOKEN_WORD))
		return (true);
	return (false);
}

/*
** cmd_suffix :            io_redirect
**            | cmd_suffix io_redirect
**			  |            WORD
**			  | cmd_suffix WORD
*/

int		predict_cmd_suffix(t_parser *parser, t_array *words, t_array *redirections)
{
	struct	s_redirection	*redir;
	int						ret;

	ret = NO_ERROR;
	while (ret == NO_ERROR)
	{
		if (check_requirements_io_redirect(parser))
		{
			redir = fatal_malloc(array_get_available(redirections));
			ret = predict_io_redirect(parser, redir);
		}
		else if (parser_check_current_token_type(parser, E_TOKEN_WORD))
		{
			array_push(words, parser_get_current_token(parser));
			parser_consume_token(parser);
		}
		else
			break ;
	}
	return (ret);
}
