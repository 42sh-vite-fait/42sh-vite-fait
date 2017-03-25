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

	if (var_get("CDPATH", &cdpaths) == ERROR_)
		return ;
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

//TODO: print pwd
int		cd(const char *dir, const char *home, const char *pwd, bool P)
{
	t_string	curpath;
	t_string	comp;
	int			ret;

	string_init(&curpath);
	if (dir == NULL && home == NULL)
	{
		error_set_context("no HOME");
		return (ERROR_);
	}
	else if (dir == NULL && home != NULL)
		dir = home;
	if (dir[0] == '/') /* Rule 3 */
		string_cat(&curpath, dir);
	else
	{
		string_init(&comp);
		get_next_component(&comp, curpath.str);
		if (ft_streq(comp.str, ".") || ft_streq(comp.str, "..")) /* Rule 4 */
			string_cat(&curpath, dir); /* Rule 6 */
		else
			rule_5(&curpath, dir); /* Rule 5 + 6 */
		string_shutdown(&comp);
	}
	if (P) /* Rule 7 */
		ret = physical_resolution(&curpath);
	else
		ret = logical_resolution(&curpath, pwd);
	string_shutdown(&curpath);
	return (ret);
}

int		builtin_cd(int ac, const char *const *av)
{
	const char	*dir;
	const char	*home;
	const char	*pwd;
	bool		p;
	t_opt		opt;
	char		ret;

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
	if (ac == 1)
	{
		if (!ft_strcmp(av[0], "-"))
			var_get("OLDPWD", &dir);
		else
			dir = av[0];
	}
	else
		dir = NULL;
	var_get("HOME", &home);
	var_get("PWD", &pwd);
	if (!ft_strcmp(pwd, "/"))
		pwd += 1;
	// error print
	return (cd(dir, home, pwd, p));
}
