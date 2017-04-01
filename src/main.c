/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:22:21 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:22:22 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "opt.h"
#include "shell.h"
#include "ft_printf.h"

// TODO remove
static void	check_leaks(void)
{
	char	*cmd;

	ft_asprintf(&cmd, "leaks %ld >/dev/null", getpid());
	if (system(cmd) != 0)
	{
		free(cmd);
		ft_asprintf(&cmd, "leaks %ld", getpid());
		system(cmd);
		exit(-2);
	}
	free(cmd);
}

int		main(int argc, char *argv[])
{
	extern char	**environ;
	int			ret;

	init_shell(argc, (const char *const*)argv, environ);
	ret = shell_loop();
	if (opt_is_set(OPT_INTERACTIVE))
		shell_history_shutdown();
	if (getenv("CHECK_LEAKS"))
		check_leaks();
	return (ret);
}
