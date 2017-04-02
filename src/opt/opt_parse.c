/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:24:06 by djean             #+#    #+#             */
/*   Updated: 2017/04/02 12:37:37 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "unistd_42.h"
#include "opt.h"
#include "shell.h"
#include "ft_printf.h"

unsigned			g_opt_shell;
static const char	*g_opt_command_line;

static void		usage(void)
{
	const char	*usage = "usage:  %s [option] [cstring]\n"

	"        %s -c cmd\n";
	ft_dprintf(2, usage, BIN_NAME, BIN_NAME, BIN_NAME);
	exit(1);
}

const char		*opt_get_command_line(void)
{
	assert(g_opt_command_line != NULL);
	return (g_opt_command_line);
}

void			opt_parse(int argc, const char *const *argv)
{
	t_opt	opt;
	int		ch;

	(void)argc;
	OPT_INIT(opt);
	while ((ch = ft_getopt(argv, "c:", &opt)) != -1)
	{
		if (ch == 'c')
		{
			g_opt_command_line = opt.arg;
			g_opt_shell |= (OPT_CMD_STRING);
		}
		else
			usage();
	}
	if (!opt_is_set(OPT_CMD_STRING) && isatty(STDIN_FILENO))
		g_opt_shell |= OPT_INTERACTIVE;
}
