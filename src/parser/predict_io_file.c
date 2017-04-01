/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_io_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:36:32 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:36:33 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	check_requirements_io_file(const t_parser *parser)
{
	if (parser_check_current_token_type(parser, E_TOKEN_LESS)
			|| parser_check_current_token_type(parser, E_TOKEN_LESSAND)
			|| parser_check_current_token_type(parser, E_TOKEN_GREAT)
			|| parser_check_current_token_type(parser, E_TOKEN_GREATAND)
			|| parser_check_current_token_type(parser, E_TOKEN_DGREAT)
			|| parser_check_current_token_type(parser, E_TOKEN_LESSGREAT))
		return (true);
	return (false);
}

/*
** io_file : '<'       filename
**         | LESSAND   filename
**		   | '>'       filename
**		   | GREATAND  filename
**		   | DGREAT    filename
**		   | LESSGREAT filename
*/

int		predict_io_file(t_parser *parser)
{
	if (check_requirements_io_file(parser))
	{
		parser_consume_token(parser);
		return (parser_consume_if_match(parser, E_TOKEN_WORD));
	}
	return (ERROR_);
}
