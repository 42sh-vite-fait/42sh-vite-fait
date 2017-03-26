#include <stdbool.h>
#include <stddef.h>
#include "var.h"
#include "string_42.h"
#include "misc.h"
#include "errors.h"
#include "builtins.h"
#include "unistd_42.h"
#include "ft_printf.h"

static void	rule_5(t_string *curpath, const char *dir)
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

	if (chdir(curpath->str) == -1)
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

int		logical_resolution(t_string *curpath, const char *pwd)
{
	t_string	backup;

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
	return (0);
}

void	get_base_path(t_string *curpath, const char *dir)
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
			rule_5(curpath, dir); /* Rule 5 + 6 */
		string_shutdown(&comp);
	}

}

const char	*get_dir(const char *arg, const char *home)
{
	const char	*dir;

	if (arg != NULL)
	{
		if (!ft_strcmp(arg, "-"))
			var_get("OLDPWD", &dir);
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

//TODO: print pwd
int		cd(const char *arg, bool P)
{
	t_string	curpath;
	int			ret;
	const char	*pwd;
	const char	*home;
	const char	*dir;

	var_get("HOME", &home);
	var_get("PWD", &pwd);
	dir = get_dir(arg, home);
	if (dir == NULL)
		return (ERROR_);
	string_init(&curpath);
	get_base_path(&curpath, dir);
	printf("coucou !!! %s | %s\n", dir, curpath.str);
	if (P) /* Rule 7 */
		ret = physical_resolution(&curpath);
	else
		ret = logical_resolution(&curpath, pwd);
	string_shutdown(&curpath);
	return (ret);
}

int		builtin_cd(int ac, const char *const *av)
{
	bool		p;
	t_opt		opt;
	char		ret;
	int			ret_value;

	OPT_INIT(opt);
	p = false;
	opt.print_errmsg = true;
	while ((ret = ft_getopt(av, "PL", &opt)) != -1)
	{
		if (ret == '?' || ret == ':')
			return (1);
		else if (ret == 'P')
			p = true;
		else if (ret == 'L')
			p = false;
	}
	ac -= opt.end;
	if (ac >= 2)
	{
		ft_dprintf(2, "usage: %s [-L|-P] [directory]\n", av[0]);
		return (1);
	}
	av += opt.end;
	/* if (!ft_strcmp(pwd, "/")) */
	/* 	pwd += 1; */
	ret_value = cd(ac == 1 ? av[0] : NULL, p);
	if (ret_value == ERROR_)
		error_print("cd");
	return (ret_value);
}
