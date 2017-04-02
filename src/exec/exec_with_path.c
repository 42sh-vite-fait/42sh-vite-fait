/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_with_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:01:48 by djean             #+#    #+#             */
/*   Updated: 2017/04/02 12:28:02 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <assert.h>
#include "errors.h"
#include "string_42.h"
#include "exec.h"
#include "misc.h"
#include "array_42.h"

#define ERROR			(-1)
#define NO_MORE_PATH	(0)
#define PATH_FOUND 		(1)

#define FALLBACK_SH_PATH	("/bin/sh")

/*
** Why ?
** http://pubs.opengroup.org/onlinepubs/9699919799/functions/exec.html
*/

static void	exec_fallback_no_shebang(const char *path, char *const *av,
		char *const *envp)
{
	t_array		argv;
	const char	*sh_path;

	fatal_malloc(array_init(&argv, sizeof(char*)));
	sh_path = FALLBACK_SH_PATH;
	fatal_malloc(array_push(&argv, &sh_path));
	fatal_malloc(array_push(&argv, &path));
	av += 1;
	while (*av)
	{
		fatal_malloc(array_push(&argv, av));
		av += 1;
	}
	fatal_malloc(array_push(&argv, av));
	execve(FALLBACK_SH_PATH, argv.data, envp);
}

static int	try_exec_path(const char *paths, char *const *av,
		char *const *envp)
{
	t_string	test;
	int			error;

	string_init(&test);
	error = ENOENT;
	while ((paths = get_next_path(&test, paths)) != NULL)
	{
		if (is_dir(test.str))
		{
			fatal_malloc(string_cat(&test, av[0]));
			execve(test.str, av, envp);
			if (errno == ENOEXEC)
				exec_fallback_no_shebang(test.str, av, envp);
			if (errno != ENOENT)
				error = errno;
		}
	}
	string_shutdown(&test);
	return (error);
}

static void	exec_handle_error(const char *cmd, int error)
{
	if (error == ENOENT)
		error_set_context("command not found: %s", cmd);
	else
		error_set_context("%s: %s", strerror(error), cmd);
	error_print("execution");
	if (error == ENOENT || error == ENOTDIR || error == ELOOP)
		_exit(127);
	else if (error == EACCES)
		_exit(126);
	else
		_exit(error);
}

void		exec_with_path(const char *paths, char *const *av,
		char *const *envp)
{
	int	error;

	assert(paths != NULL);
	assert(av != NULL);
	assert(av[0] != NULL);
	assert(envp != NULL);
	if (ft_strchr(av[0], '/') != NULL)
	{
		execve(av[0], av, envp);
		if (errno == ENOEXEC)
			exec_fallback_no_shebang(av[0], av, envp);
		error = errno;
	}
	else
		error = try_exec_path(paths, av, envp);
	exec_handle_error(av[0], error);
}
