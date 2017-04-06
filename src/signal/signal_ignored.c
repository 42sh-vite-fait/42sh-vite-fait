/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_ignored.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:39:25 by djean             #+#    #+#             */
/*   Updated: 2017/04/08 15:13:34 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include "macros_42.h"
#include "memory_42.h"
#include "sig.h"

extern const int	g_signals_to_ignore[];
extern const size_t	g_signals_to_ignore_len;

void	signal_set_ignored_signals(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(struct sigaction));
	act.sa_handler = SIG_IGN;
	signal_set_handler_for(g_signals_to_ignore, g_signals_to_ignore_len, &act);
}

void	signal_unset_ignored_signals(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(struct sigaction));
	act.sa_handler = SIG_DFL;
	signal_set_handler_for(g_signals_to_ignore, g_signals_to_ignore_len, &act);
}
