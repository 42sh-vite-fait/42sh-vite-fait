/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fallback_sh.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:01:48 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:01:52 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "array_42.h"
#include "exec.h"

#define FALLBACK_SH_PATH	("/bin/sh")

/*
** Why ?
** http://pubs.opengroup.org/onlinepubs/9699919799/functions/exec.html
*/

void	exec_fallback_no_shebang(const char *path, char *const *av,
		char *const *envp)
{
	t_array		argv;
	const char	*sh_path;

	array_init(&argv, sizeof(char*));
	sh_path = FALLBACK_SH_PATH;
	array_push(&argv, &sh_path);
	array_push(&argv, &path);
	av += 1;
	while (*av)
	{
		array_push(&argv, av);
		av += 1;
	}
	array_push(&argv, av);
	execve(FALLBACK_SH_PATH, argv.data, envp);
}
