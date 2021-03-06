/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_io_here.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:36:32 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:36:33 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	redir->heredoc_filename = NULL;
	parser_heredoc_push(parser, redir);
	return (OK_);
}
