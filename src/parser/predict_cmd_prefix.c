/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_cmd_prefix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:36:32 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:36:33 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	check_requirements_cmd_prefix(const t_parser *parser)
{
	if (check_requirements_io_redirect(parser))
		return (true);
	return (false);
}

/*
** cmd_prefix :            io_redirect
**            | cmd_prefix io_redirect
*/

int		predict_cmd_prefix(t_parser *parser, t_array *redirections)
{
	struct s_redirection	*redir;
	int						ret;

	ret = OK_;
	while (ret == OK_)
	{
		if (check_requirements_io_redirect(parser))
		{
			redir = fatal_malloc(array_get_available(redirections));
			ret = predict_io_redirect(parser, redir);
		}
		else
			break ;
	}
	return (ret);
}
