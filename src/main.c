/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:22:21 by djean             #+#    #+#             */
/*   Updated: 2017/04/02 17:42:11 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "opt.h"
#include "shell.h"

int		main(int argc, char *argv[])
{
	extern char	**environ;
	int			ret;

	init_shell(argc, (const char *const*)argv, environ);
	ret = shell_loop();
	if (opt_is_set(OPT_INTERACTIVE))
		shell_history_shutdown();
	return (ret);
}
