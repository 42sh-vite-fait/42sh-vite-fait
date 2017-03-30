/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 17:00:15 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 17:28:12 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include <signal.h>
# include <stdbool.h>

# define SIGACT_NO_FLAG	0

typedef void	(*t_sig) (int);

void	init_signal_module(void);
void	signal_set_input_context(void);
void	signal_set_post_input_context(void);
void	signal_set_handler_for(const int sigs[], size_t len,
		const struct sigaction *act);

/*
** Blocked signals
*/
bool	signal_should_we_restart_the_loop(void);
void	signal_block_exit_signals(void);
void	signal_unblock_exit_signals(void);

/*
** Ignored signals
*/
void	signal_set_ignored_signals(void);
void	signal_unset_ignored_signals(void);

/*
** Input signals
*/
void	signal_mute_exit_signals(void);
void	signal_unmute_exit_signals(void);

#endif
