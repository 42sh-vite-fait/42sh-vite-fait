/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_jump.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:19:58 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:20:01 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user_interface.h"

void		ui_handler_jump_end(t_term_env *env, char c)
{
	int	offset;

	(void)c;
	offset = (int)(env->line.str->len - env->line.string_index);
	line_move_cursor(&env->line, offset);
	env->line.string_index += offset;
}

void		ui_handler_jump_start(t_term_env *env, char c)
{
	(void)c;
	line_move_cursor(&env->line, -(int)env->line.string_index);
	env->line.string_index -= env->line.string_index;
}

void		ui_handler_jump_next_word(t_term_env *env, char c)
{
	int		offset;

	(void)c;
	offset = (int)line_next_word_size(&env->line);
	line_move_cursor(&env->line, offset);
	env->line.string_index += offset;
}

void		ui_handler_jump_prev_word(t_term_env *env, char c)
{
	int		offset;

	(void)c;
	offset = (int)line_prev_word_size(&env->line);
	line_move_cursor(&env->line, -offset);
	env->line.string_index -= (size_t)offset;
}
