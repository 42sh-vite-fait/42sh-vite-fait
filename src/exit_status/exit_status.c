/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:18:19 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:18:35 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"

static int g_exit_status_last = 0;

int		exit_status_get_last(void)
{
	return (g_exit_status_last);
}

void	exit_status_set_last(int exit_status)
{
	g_exit_status_last = exit_status;
}
