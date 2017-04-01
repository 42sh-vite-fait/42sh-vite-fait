/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_program.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:36:32 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:36:33 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** program : linebreak complete_commands linebreak
**         | linebreak
*/

int	predict_program(t_parser *parser, t_ast_node **root)
{
	if (predict_linebreak(parser) != OK_)
		return (ERROR_);
	if (check_requirements_complete_commands(parser))
	{
		if (predict_complete_commands(parser, root) != OK_)
			return (ERROR_);
		if (predict_linebreak(parser) != OK_)
			return (ERROR_);
	}
	return (OK_);
}
