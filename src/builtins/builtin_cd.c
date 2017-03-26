#include <stdbool.h>
#include <stddef.h>
#include "var.h"
#include "string_42.h"
#include "misc.h"
#include "errors.h"
#include "builtins.h"
#include "unistd_42.h"
#include "ft_printf.h"

static void	rule_5(t_string *curpath, bool *must_print_pwd, const char *dir)
{
	t_string	next;
	const char	*cdpaths;

	if (var_get("CDPATH", &cdpaths) == OK_)
	{
		string_init(&next);
		while ((cdpaths = get_next_path(&next, cdpaths)) != NULL)
		{
			string_cat(&next, dir);
			if (is_dir(next.str))
			{
				string_shutdown(curpath);
				*curpath = next;
				*must_print_pwd = cdpaths[0] != ':' && cdpaths[0] != '\0';
				return ;
			}
		}
		string_shutdown(&next);
	}
	string_cat(curpath, dir); /* Rule 6 */
}

int		physical_resolution(t_string *curpath)
{
	char	*new_pwd;

	if (chdir(curpath->str) == -1) /* Rule 10 */
	{
		error_set_context("%s: %s", curpath->str, strerror(errno));
		return (ERROR_);
	}
	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
		return (ERROR_);
	var_set("PWD", new_pwd);
	free(new_pwd);
	return (OK_);
}

int		logical_resolution(t_string *curpath)
{
	t_string	backup;
	const char	*pwd;

	backup.len = 0;
	var_get("PWD", &pwd);
	if (curpath->str[0] != '/') /* Rule 7 */
	{
		string_insert(curpath, 0, "/", 1);
		string_insert(curpath, 0, pwd, ft_strlen(pwd));
	}
	if (builtin_cd_rule_8(curpath) == -1) /* Rule 8 */
		return (ERROR_);
	if (!ft_strncmp(pwd, curpath->str, ft_strlen(pwd)) && curpath->str[ft_strlen(pwd)] == '/') 	/* Rule 9 */
	{
		string_clone(&backup, curpath);
		string_remove(curpath, 0, ft_strlen(pwd));
		string_insert(curpath, 0, ".", 1);
	}
	if (chdir(curpath->str) == -1)
	{
		error_set_context("%s: %s", curpath->str, strerror(errno));
		return (ERROR_);
	}
	var_set("OLDPWD", pwd);
	if (backup.len != 0)
		var_set("PWD", backup.str);
	else
		var_set("PWD", curpath->str);
	return (OK_);
}

void	get_base_path(t_string *curpath, bool *must_print_pwd, const char *dir)
{
	t_string	comp;

	if (dir[0] == '/') /* Rule 3 */
		string_cat(curpath, dir);
	else
	{
		string_init(&comp);
		get_next_component(&comp, curpath->str);
		if (ft_streq(comp.str, ".") || ft_streq(comp.str, "..")) /* Rule 4 */
			string_cat(curpath, dir); /* Rule 6 */
		else
			rule_5(curpath, must_print_pwd, dir); /* Rule 5 + 6 */
		string_shutdown(&comp);
	}

}

const char	*get_dir(bool *must_print_pwd, const char *arg)
{
	const char	*dir;
	const char	*home;

	var_get("HOME", &home);
	if (arg != NULL)
	{
		if (!ft_strcmp(arg, "-"))
		{
			*must_print_pwd = true;
			var_get("OLDPWD", &dir);
		}
		else
			dir = arg;
	}
	else
		dir = NULL;
	if (dir == NULL && home == NULL)
	{
		error_set_context("no home directory (HOME not set)");
		return (NULL);
	}
	else if (dir == NULL && home != NULL)
		dir = home;
	return (dir);
}

int		get_options(bool *p, const char **arg, int ac, const char *const *av)
{
	t_opt	opt;
	char	ret;

	OPT_INIT(opt);
	*p = false;
	while ((ret = ft_getopt(av, "PL", &opt)) != -1)
	{
		if (ret == '?' || ret == ':')
		{
			error_set_context("unknown option -%c", ret);
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

int		cd(int ac, const char *const *av)
{
	t_string	curpath;
	int			ret;
	const char	*dir;
	const char	*arg;
	bool		is_cd_physical;
	bool		must_print_pwd;

	must_print_pwd = false;
	if (get_options(&is_cd_physical, &arg, ac, av) == ERROR_)
		return (ERROR_);
	dir = get_dir(&must_print_pwd, arg);
	if (dir == NULL)
		return (ERROR_);
	string_init(&curpath);
	get_base_path(&curpath, &must_print_pwd, dir);
	if (is_cd_physical) /* Rule 7 */
		ret = physical_resolution(&curpath);
	else
		ret = logical_resolution(&curpath);
	if (ret == OK_ && must_print_pwd)
		ft_printf("%s\n", curpath.str);
	string_shutdown(&curpath);
	return (ret);
}

int		builtin_cd(int ac, const char *const *av)
{
	if (cd(ac, av) == OK_)
		return (0);
	error_print("cd");
	return (1);
}
