/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 17:45:43 by rcargou           #+#    #+#             */
/*   Updated: 2016/09/27 19:46:02 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ui.h>

int 		tputs_write(int c)
{
	write(0, &c, 1);
	return (0);
}

void        term_command(char *entry)
{
	char *res;

	res = tgetstr(entry, NULL);
	tputs(res, 0, tputs_write);
}

t_cursor 	term_get_cursor()
{

}

void		term_newine()
{
	term_command("nw");
}

void 		term_move_cursor(int x, int y)
{

}
