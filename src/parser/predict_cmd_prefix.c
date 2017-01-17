#include "parser.h"

bool	check_requirements_cmd_prefix(const t_parser *parser)
{
	if (check_requirements_io_redirect(parser)
			|| parser_check_current_token_type(parser, E_TOKEN_ASSIGNMENT_WORD))
		return (true);
	return (false);
}

/*
** cmd_prefix :            io_redirect
**            | cmd_prefix io_redirect
**			  |            ASSIGNMENT_WORD
**			  | cmd_prefix ASSIGNMENT_WORD
*/

int		predict_cmd_prefix(t_parser *parser, t_array *redirections, t_array *assignments)
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
		else if (parser_check_current_token_type(parser, E_TOKEN_ASSIGNMENT_WORD))
		{
			array_push(assignments, parser_get_current_token(parser));
			parser_consume_token(parser);
		}
		else
			break ;
	}
	return (ret);
}
