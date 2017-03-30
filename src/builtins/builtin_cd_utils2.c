#include "string_42.h"
#include "errors.h"
#include "builtins.h"
#include "var.h"

extern t_string	g_pwd;

int			cd_set_pwd(void)
{
	const char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (ERROR_);
	fatal_malloc(string_init_dup(&g_pwd, pwd));
	free((void*)pwd);
	return (OK_);
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
		fatal_malloc(string_cat(component, path));
		return (ft_strchr(path, '\0'));
	}
	fatal_malloc(string_ncat(component, path, sep));
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
	{
		error_set_context("%s", strerror(errno));
		return (ERROR_);
	}
	var_set("OLDPWD", g_pwd.str);
	var_set("PWD", new_pwd);
	fatal_malloc(string_replace(curpath, new_pwd));
	free(new_pwd);
	return (OK_);
}
