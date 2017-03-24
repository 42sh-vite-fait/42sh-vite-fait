#include "parser.h"

bool	check_requirements_redirect_list(const t_parser *parser)
{
	if (check_requirements_io_redirect(parser))
		return (true);
	return (false);
}

/*
** redirect_list :               io_redirect
**               | redirect_list io_redirect
*/

int		predict_redirect_list(t_parser *parser, t_array *redirections)
{
	struct s_redirection	*redir;

	redir = fatal_malloc(array_get_available(redirections));
	if (predict_io_redirect(parser, redir) != OK_)
		return (ERROR_);
	while (check_requirements_io_redirect(parser))
	{
		redir = fatal_malloc(array_get_available(redirections));
		if (predict_io_redirect(parser, redir) != OK_)
			return (ERROR_);
	}
	return (OK_);
}
