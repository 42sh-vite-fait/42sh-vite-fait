/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shutdown_term_env.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:19:58 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:20:01 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_42.h"
#include "user_interface.h"
#include "array_42.h"

void	term_env_clear_autocompletion(t_term_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->autocomplete_matches.len)
	{
		free(*(char **)array_get_at(&env->autocomplete_matches, i));
		i += 1;
	}
	array_clear(&env->autocomplete_matches);
}

void	init_term_env(t_term_env *env, t_string *line, const char *prompt)
{
	env->line.str = line;
	env->line.string_index = 0;
	env->prompt_size = ft_strlen(prompt);
	env->line.cursor_x = env->prompt_size;
	term_env_update_for_resize(env);
	string_init(&env->kill_buffer);
	env->history_index = 0;
	env->autocomplete_index = 0;
	env->autocomplete_state = E_NO_AUTOCOMPLETE;
	array_init(&env->autocomplete_matches, sizeof(char *));
}

void	shutdown_term_env(t_term_env *env)
{
	term_env_clear_autocompletion(env);
	string_shutdown(&env->kill_buffer);
	array_shutdown(&env->autocomplete_matches);
}
