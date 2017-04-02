/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 15:23:11 by djean             #+#    #+#             */
/*   Updated: 2017/04/02 15:23:13 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "typedefs_42.h"
#include "cbuffer_42.h"
#include "history.h"
#include "error_42.h"

extern t_history	g_history;
t_history			g_history;

int				history_init(size_t limit)
{
	fatal_malloc(cbuffer_init(&g_history.commands, limit, sizeof(t_string),
								(void (*)(void *))string_shutdown));
	g_history.last_id = 0;
	return (0);
}

void			history_shutdown(void)
{
	cbuffer_shutdown(&g_history.commands);
}
