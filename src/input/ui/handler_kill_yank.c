/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_kill_yank.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:19:58 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:20:01 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user_interface.h"
#include "str_42.h"

char	*g_kill_buffer = NULL;

void		ui_handler_kill_left(t_term_env *env, char c)
{
	(void)c;
	if (g_kill_buffer != NULL)
		free(g_kill_buffer);
	g_kill_buffer = ft_strsub(env->line.str->str, 0, env->line.string_index);
	fatal_malloc(g_kill_buffer);
	line_remove_left(&env->line, env->line.string_index);
}

void		ui_handler_kill_right(t_term_env *env, char c)
{
	size_t	kill_start;
	size_t	kill_size;

	(void)c;
	kill_start = env->line.string_index;
	kill_size = env->line.str->len - env->line.string_index;
	if (g_kill_buffer != NULL)
		free(g_kill_buffer);
	g_kill_buffer = ft_strsub(env->line.str->str, kill_start, kill_size);
	fatal_malloc(g_kill_buffer);
	line_remove_right(&env->line, kill_size);
}

void		ui_handler_kill_left_word(t_term_env *env, char c)
{
	size_t	word_size;
	size_t	word_start;

	(void)c;
	word_size = line_prev_word_size(&env->line);
	word_start = env->line.string_index - word_size;

	if (g_kill_buffer != NULL)
		free(g_kill_buffer);
	g_kill_buffer = ft_strsub(env->line.str->str, word_start, word_size);
	fatal_malloc(g_kill_buffer);
	line_remove_left(&env->line, word_size);
}

void		ui_handler_kill_right_word(t_term_env *env, char c)
{
	size_t	word_size;
	size_t	word_start;

	(void)c;
	word_size = line_next_word_size(&env->line);
	word_start = env->line.string_index;
	if (g_kill_buffer != NULL)
		free(g_kill_buffer);
	g_kill_buffer = ft_strsub(env->line.str->str, word_start, word_size);
	fatal_malloc(g_kill_buffer);
	line_remove_right(&env->line, word_size);
}

void		ui_handler_yank(t_term_env *env, char c)
{
	(void)c;
	if (g_kill_buffer != NULL)
		line_insert(&env->line, g_kill_buffer, ft_strlen(g_kill_buffer));
}
