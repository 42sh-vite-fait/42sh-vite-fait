/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_compound_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:36:32 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:36:33 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	check_requirements_compound_list(const t_parser *parser)
{
	if (check_requirements_linebreak(parser))
		return (true);
	return (false);
}

/*
** compound_list : linebreak term
**               | linebreak term separator
*/

int		predict_compound_list(t_parser *parser, t_ast_node **from_parent)
{
	if (predict_linebreak(parser) != OK_)
		return (ERROR_);
	if (predict_term(parser, from_parent) != OK_)
		return (ERROR_);
	if (check_requirements_separator(parser))
		return (predict_separator(parser));
	return (OK_);
}
