/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:19:58 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:20:01 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user_interface.h"
#include "history.h"

void	ui_handler_history_prev(t_term_env *env, char c)
{
	const	t_string	*entry;

	(void)c;
	entry = history_get(history_get_last_id() - env->history_index);
	if (entry != NULL)
	{
		env->history_index += 1;
		line_replace(&env->line, entry->str, entry->len);
	}
}

void	ui_handler_history_next(t_term_env *env, char c)
{
	const	t_string	*entry;

	(void)c;
	if (env->history_index > 1)
	{
		entry = history_get(history_get_last_id() - (env->history_index - 2));
		if (entry != NULL)
		{
			env->history_index -= 1;
			line_replace(&env->line, entry->str, entry->len);
		}
	}
	else if (env->history_index == 1)
	{
		env->history_index = 0;
		line_replace(&env->line, "", 0);
	}
}
