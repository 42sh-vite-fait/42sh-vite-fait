#include "string_42.h"
#include "builtins.h"
#include "var.h"
#include "misc.h"
#include "errors.h"

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

const char	*get_next_component(t_string *component, const char *path)
{
	ssize_t		sep;

	if (path[0] == '\0')
		return (NULL);
	string_truncate(component, 0);
	sep = ft_strchrpos(path, '/');
	if (sep == -1)
	{
		string_cat(component, path);
		return (ft_strchr(path, '\0'));
	}
	string_ncat(component, path, sep);
	while (path[sep] == '/')
		sep += 1;
	return (path + sep);
}

int			physical_resolution(t_string *curpath)
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

int			logical_resolution(t_string *curpath, t_string backup,
							const char *pwd)
{
	backup.len = 0;
	var_get("PWD", &pwd);
	if (curpath->str[0] != '/')
	{
		string_insert(curpath, 0, "/", 1);
		string_insert(curpath, 0, pwd, ft_strlen(pwd));
	}
	if (builtin_cd_rule_8(curpath) == -1)
		return (ERROR_);
	if (!ft_strncmp(pwd, curpath->str, ft_strlen(pwd))
		&& curpath->str[ft_strlen(pwd)] == '/')
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
	var_set("PWD", backup.len != 0 ? backup.str : curpath->str);
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
