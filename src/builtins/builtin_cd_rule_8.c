#include <stdbool.h>
#include <sys/stat.h>
#include "string_42.h"
#include "errors.h"
#include "misc.h"
#include "builtins.h"

extern t_string	g_pwd;

int					cd_set_pwd(void)
{
	const char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (ERROR_);
	fatal_malloc(string_init_dup(&g_pwd, pwd));
	return (OK_);
}

static int			rewind_path(t_string *curpath)
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

int					builtin_cd_rule_8(t_string *curpath)
{
	t_string	component;
	t_string	build_path;
	const char	*path;

	string_init(&component);
	string_init(&build_path);
	path = curpath->str;
	while ((path = get_next_component(&component, path)) != NULL)
	{
		if (ft_streq(component.str, ".."))
		{
			if (rewind_path(&build_path) == ERROR_)
				return (ERROR_);
		}
		else if (!ft_streq(component.str, "."))
		{
			string_append(&build_path, &component);
			string_ncat(&build_path, "/", 1);
		}
	}
	string_shutdown(curpath);
	string_shutdown(&component);
	if (build_path.len > 1 && build_path.str[build_path.len - 1] == '/')
		string_remove_back(&build_path, 1);
	*curpath = build_path;
	return (OK_);
}
