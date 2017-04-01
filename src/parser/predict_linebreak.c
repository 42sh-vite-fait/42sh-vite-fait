/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_linebreak.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:36:32 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:36:33 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	check_requirements_linebreak(const t_parser *parser)
{
	(void)parser;
	return (true);
}

/*
** linebreak : newline_list
**           | // empty
*/

int		predict_linebreak(t_parser *parser)
{
	if (check_requirements_newline_list(parser))
		predict_newline_list(parser);
	return (OK_);
}
