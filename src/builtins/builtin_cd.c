/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 19:53:15 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 19:53:16 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "var.h"
#include "string_42.h"
#include "errors.h"
#include "builtins.h"
#include "unistd_42.h"
#include "ft_printf.h"

t_string	g_pwd;

static const char	*get_dir(bool *must_print_pwd, const char *dir)
{
	const char	*home;

	var_get("HOME", &home);
	if (dir != NULL)
	{
		if (!ft_strcmp(dir, "-"))
		{
			*must_print_pwd = true;
			if (var_get("OLDPWD", &dir) != OK_)
			{
				error_set_context("no OLDPWD");
				return (NULL);
			}
		}
	}
	else if (home == NULL)
		error_set_context("no home directory (HOME not set)");
	else
		dir = home;
	return (dir);
}

static int			get_options(bool *p, const char **arg, int ac,
								const char *const *av)
{
	t_opt	opt;
	char	ret;

	OPT_INIT(opt);
	*p = false;
	while ((ret = ft_getopt(av, "PL", &opt)) != -1)
	{
		if (ret == '?' || ret == ':')
		{
			error_set_context("unknown option -%c", opt.unknown_opt);
			return (ERROR_);
		}
		else if (ret == 'P')
			*p = true;
		else if (ret == 'L')
			*p = false;
	}
	if (ac - opt.end > 1)
	{
		error_set_context("usage: %s [-L|-P] [directory]", av[0]);
		return (ERROR_);
	}
	*arg = av[opt.end];
	return (OK_);
}

static int			cd(int ac, const char *const *av)
{
	t_string	curpath;
	int			ret;
	const char	*dir;
	bool		is_cd_physical;
	bool		must_print_pwd;

	must_print_pwd = false;
	if (get_options(&is_cd_physical, &dir, ac, av) == ERROR_)
		return (ERROR_);
	dir = get_dir(&must_print_pwd, dir);
	if (dir == NULL)
		return (ERROR_);
	fatal_malloc(string_init(&curpath));
	get_base_path(&curpath, &must_print_pwd, dir);
	if (is_cd_physical)
		ret = physical_resolution(&curpath);
	else
		ret = logical_resolution(&curpath, g_pwd.str, g_pwd.len);
	if (ret == OK_ && must_print_pwd)
		ft_printf("%s\n", curpath.str);
	if (ret != ERROR_)
		fatal_malloc(string_replace(&g_pwd, curpath.str));
	string_shutdown(&curpath);
	return (ret);
}

int					builtin_cd(int ac, const char *const *av)
{
	if (cd(ac, av) == OK_)
		return (0);
	error_print("cd");
	return (1);
}
