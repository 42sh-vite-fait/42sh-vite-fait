/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_get_winsize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:19:58 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:20:01 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "terminal.h"
#include "user_interface.h"

static struct winsize	terminal_get_winsize(void)
{
	int				ret;
	struct winsize	sizes;

	assert(isatty(STDIN_FILENO));
	ret = ioctl(STDIN_FILENO, TIOCGWINSZ, &sizes);
	assert(ret != -1);
	return (sizes);
}

void					term_env_update_for_resize(t_term_env *env)
{
	env->line.term_x = terminal_get_winsize().ws_col;
	if (env->line.term_x == 0)
		env->line.term_x = 1;
	env->line.cursor_x = (env->prompt_size + env->line.string_index)
		% (env->line.term_x);
}
