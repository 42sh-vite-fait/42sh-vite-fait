#include <stdbool.h>
#include <stddef.h>
#include "var.h"
#include "string_42.h"
#include "misc.h"
#include "errors.h"
#include "builtins.h"
#include "unistd_42.h"
#include "ft_printf.h"

static const char	*get_dir(bool *must_print_pwd, const char *arg)
{
	const char	*dir;
	const char	*home;

	var_get("HOME", &home);
	if (arg != NULL)
	{
		if (!ft_strcmp(arg, "-"))
		{
			*must_print_pwd = true;
			if (var_get("OLDPWD", &dir) != OK_)
			{
				error_set_context("no OLDPWD");
				return (NULL);
			}
		}
		else
			dir = arg;
	}
	else
		dir = NULL;
	if (dir == NULL && home == NULL)
		error_set_context("no home directory (HOME not set)");
	else if (dir == NULL && home != NULL)
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
	*arg = ac - opt.end == 1 ? av[opt.end] : NULL;
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
	string_init(&curpath);
	get_base_path(&curpath, &must_print_pwd, dir);
	if (is_cd_physical)
		ret = physical_resolution(&curpath);
	else
		ret = logical_resolution(&curpath, curpath, dir);
	if (ret == OK_ && must_print_pwd)
		ft_printf("%s\n", curpath.str);
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
