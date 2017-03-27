#include "string_42.h"
#include "builtins.h"
#include "var.h"
#include "misc.h"
#include "errors.h"

t_string	g_pwd;

static void	rule_5(t_string *curpath, bool *must_print_pwd, const char *dir)
{
	t_string	next;
	const char	*cdpaths;
	const char	*current;

	if (var_get("CDPATH", &cdpaths) == OK_)
	{
		current = cdpaths;
		string_init(&next);
		while ((cdpaths = get_next_path(&next, cdpaths)) != NULL)
		{
			string_cat(&next, dir);
			if (is_dir(next.str))
			{
				string_shutdown(curpath);
				*curpath = next;
				*must_print_pwd = current[0] != ':';
				return ;
			}
			current = cdpaths;
		}
		string_shutdown(&next);
	}
	string_cat(curpath, dir);
}

static int	rewind_path(t_string *curpath)
{
	if (!is_dir(curpath->str))
	{
		error_set_context("%s: %s", curpath->str, strerror(errno));
		return (ERROR_);
	}
	string_remove_back(curpath, 1);
	string_remove_back_chr(curpath, '/');
	string_cat(curpath, "/");
	return (OK_);
}

static int	builtin_cd_rule_8(t_string *curpath)
{
	t_string	component;
	t_string	build_path;
	const char	*path;

	string_init(&component);
	string_init(&build_path);
	path = curpath->str;
	while ((path = get_next_component(&component, path)) != NULL)
	{
		if (!ft_streq(component.str, ".") && !ft_streq(component.str, ".."))
		{
			string_append(&build_path, &component);
			string_ncat(&build_path, "/", 1);
		}
		else if (ft_streq(component.str, "..") &&
				rewind_path(&build_path) == ERROR_)
			return (ERROR_);
	}
	string_shutdown(curpath);
	string_shutdown(&component);
	if (build_path.len > 1 && build_path.str[build_path.len - 1] == '/')
		string_remove_back(&build_path, 1);
	*curpath = build_path;
	return (OK_);
}

int			logical_resolution(t_string *curpath, t_string chdir_path,
							const char *pwd)
{
	pwd = g_pwd.str;
	if (curpath->str[0] != '/')
	{
		string_insert(curpath, 0, "/", 1);
		string_insert(curpath, 0, pwd, ft_strlen(pwd));
	}
	if (builtin_cd_rule_8(curpath) == -1)
		return (ERROR_);
	string_clone(&chdir_path, curpath);
	if (!ft_strncmp(pwd, curpath->str, ft_strlen(pwd))
		&& curpath->str[ft_strlen(pwd)] == '/')
	{
		string_remove(&chdir_path, 0, ft_strlen(pwd));
		string_insert(&chdir_path, 0, ".", 1);
	}
	if (chdir(chdir_path.str) == -1)
	{
		error_set_context("%s: %s", chdir_path.str, strerror(errno));
		return (ERROR_);
	}
	var_set("OLDPWD", pwd);
	var_set("PWD", curpath->str);
	string_replace(&g_pwd, curpath->str);
	return (OK_);
}

void		get_base_path(t_string *curpath, bool *must_print_pwd,
						const char *dir)
{
	t_string	comp;

	if (dir[0] == '/')
		string_cat(curpath, dir);
	else
	{
		string_init(&comp);
		get_next_component(&comp, curpath->str);
		if (ft_streq(comp.str, ".") || ft_streq(comp.str, ".."))
			string_cat(curpath, dir);
		else
			rule_5(curpath, must_print_pwd, dir);
		string_shutdown(&comp);
	}
}
