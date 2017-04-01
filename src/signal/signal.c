/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:39:24 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:39:26 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdlib.h>
#include <signal.h>
#include "sig.h"
#include "macros_42.h"

const int		g_signals_to_ignore[] = {
	SIGTTIN,
	SIGTTOU,
	SIGTSTP,
	SIGALRM,
};
const int		g_exit_signals[] = {
	SIGINT,
	SIGQUIT,
	SIGTERM,
};
const size_t	g_signals_to_ignore_len = ARR_SIZ_MAX(g_signals_to_ignore);
const size_t	g_exit_signals_len = ARR_SIZ_MAX(g_exit_signals);

/*
** Must be call only if the shell is in interactive mode TODO
*/

void	init_signal_module(void)
{
	signal_set_ignored_signals();
	signal_block_exit_signals();
}

// TODO doit être hook à la fin de la shell loop, avant de refaire un tour
void	signal_set_input_context(void)
{
	signal_mute_exit_signals();
	signal_unblock_exit_signals();
}

// TODO doit être call à la sortie du module d'input
void	signal_set_post_input_context(void)
{
	signal_block_exit_signals();
}

void	signal_set_handler_for(const int sigs[], size_t len,
		const struct sigaction *act)
{
	size_t	i;
	int		ret;

	i = 0;
	while (i < len)
	{
		ret = sigaction(sigs[i], act, NULL);
		assert(ret == 0);
		i += 1;
	}
	(void)ret;
}
