/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:39:24 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:40:10 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdbool.h>
#include "macros_42.h"
#include "memory_42.h"
#include "sig.h"

extern const int				g_exit_signals[];
extern const size_t				g_exit_signals_len;

static void	signal_handler_mark_interruption(int sig)
{
	(void)sig;
}

void		signal_mute_exit_signals(void)
{
	struct sigaction	act;
	sigset_t			emptyset;

	sigemptyset(&emptyset);
	act.sa_handler = &signal_handler_mark_interruption;
	act.sa_mask = emptyset;
	act.sa_flags = SIGACT_NO_FLAG;
	signal_set_handler_for(g_exit_signals, g_exit_signals_len, &act);
}

void		signal_unmute_exit_signals(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(struct sigaction));
	act.sa_handler = SIG_DFL;
	signal_set_handler_for(g_exit_signals, g_exit_signals_len, &act);
}
