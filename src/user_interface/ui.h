/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 17:18:58 by rcargou           #+#    #+#             */
/*   Updated: 2016/09/27 19:44:05 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include <ftsh.h>

typedef struct 	s_cursor 	t_cursor;
typedef struct 	s_editenv 	t_editenv;

struct 						s_cursor
{
	int 		x;
	int 		y;
};

struct 						s_editenv
{
	t_buffer	entry;
	t_buffer	rbuff;
};

void        				term_command(char *entry);
void						term_newine();
void 						term_clear();
void 						term_move_cursor(int x, int y);

#endif
