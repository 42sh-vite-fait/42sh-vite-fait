#include <stdbool.h>
#include <stddef.h>
#include "var.h"
#include "string_42.h"
#include "misc.h"
#include "errors.h"
#include "builtins.h"
#include "unistd_42.h"

const char	*get_next_component(t_string *next, const char *from)
{
	size_t	i;

	i = 0;
	while (from[i] && from[i] != '/')
		i += 1;
	string_truncate(next, 0);
	string_ncat(next, from, i);
	return (from + i);
}

#include <sys/stat.h>

static bool		is_dir(const char *file)
{
	struct stat	file_stat;

	return (stat(file, &file_stat) == 0 &&
			S_ISDIR(file_stat.st_mode));
}

static void	rule_5(t_string *curpath, const char *dir)
{
	const char	*tmp;
	t_string	next;

	string_init(&next);
	tmp = curpath->str;
	while ((tmp = get_next_path(&next, tmp)) != NULL)
	{
		string_cat(&next, dir);
		if (is_dir(next.str))
		{
			*curpath = next;
			return ;
		}
	}
	string_cat(curpath, dir); /* Rule 6 */
}

static int	rule_8(t_string *curpath)
{
	char	*tmp;
	char	*prev_component;
	size_t	i;
	char	*root;

	root = curpath->str;
	tmp = curpath->str;
	prev_component = NULL;
	while (*root == '/')
		root += 1;
	while (*tmp)
	{
		if (tmp[0] == '.' && (!tmp[1] || tmp[1] == '/'))
		{
			i = 1;
			while (tmp[i] == '/')
				i += 1;
			string_remove(curpath, tmp - curpath->str, i);
		}
		else if (tmp[0] == '.' && tmp[1] == '.' && (!tmp[2] || tmp[2] == '/'))
		{
			if  (prev_component != NULL && (prev_component[0] != '.' || prev_component[1] != '.' || prev_component[2] != '/'))
			{
				tmp[-1] = '\0';
				if (!is_dir(curpath->str))
				{
					error_set_context("%s: %s", strerror(errno), curpath->str);
					return (-1);
				}
				tmp[-1] = '/';
				i = 2;
				while (tmp[i] == '/')
					i += 1;
				string_remove(curpath, prev_component - curpath->str, tmp - prev_component + i);
				tmp = prev_component;
				if (prev_component == root)
					prev_component = NULL;
				else
				{
					while (prev_component[-1] == '/')
						prev_component -= 1;
					while (prev_component[-1] != '/')
						prev_component -= 1;
				}
			}
			else if (prev_component == NULL)
			{
				i = 2;
				while (tmp[i] == '/')
					i += 1;
				string_remove(curpath, 0, i);
			}
		}
		else /* Skip one directory element */
		{
			prev_component = tmp;
			while (*tmp && *tmp != '/')
				tmp += 1;
			while (*tmp == '/')
				tmp += 1;
		}
	}
	i = 0;
	tmp = curpath->str + curpath->len - 1;
	while (tmp >= curpath->str && *tmp == '/')
	{
		tmp -= 1;
		i += 1;
	}
	if (i == curpath->len)
		i -= 1;
	if (i > 0)
		string_remove(curpath, curpath->len - i, i);
	return (0);
}

int		cd(const char *dir, const char *home, const char *pwd, bool P)
{
	t_string	curpath;
	t_string	comp;
	t_string	backup;
	bool		is_backup;
	char		*new_pwd;

	is_backup = false;
	string_init(&curpath);
	if (dir == NULL)
	{
		if (home != NULL) /* Rule 2 */
			dir = home;
		else
			return (1); /* Rule 1 */
	}
	if (dir[0] == '/') /* Rule 3 */
		string_cat(&curpath, dir);
	else
	{
		string_init(&comp);
		get_next_component(&comp, curpath.str);
		if (ft_strcmp(comp.str, ".") || ft_strcmp(comp.str, "..")) /* Rule 4 */
			string_cat(&curpath, dir); /* Rule 6 */
		else
			rule_5(&curpath, dir); /* Rule 5 + 6 */
		string_shutdown(&comp);
	}
	if (!P) /* Rule 7 */
	{
		if (curpath.str[0] != '/')
		{
			string_insert(&curpath, 0, "/", 1);
			string_insert(&curpath, 0, pwd, ft_strlen(pwd));
		}
		if (rule_8(&curpath) == -1) /* Rule 8 */
		{
			error_print("cd");
			return 1;
		}
		/* Rule 9 */
		if (!ft_strncmp(pwd, curpath.str, ft_strlen(pwd)) && curpath.str[ft_strlen(pwd)] == '/')
		{
			//TODO: Replace by string_sub_replace()
			string_clone(&backup, &curpath);
			string_remove(&curpath, 0, ft_strlen(pwd));
			string_insert(&curpath, 0, ".", 1);
			is_backup = true;
		}
	}
	if (chdir(curpath.str) == -1) /* Rule 10 */
	{
		error_set_context("%s: %s", strerror(errno), curpath.str);
		error_print("cd");
		return 1;
	}
	var_set("OLDPWD", pwd);
	if (is_backup)
		var_set("PWD", backup.str);
	else if (!P)
		var_set("PWD", curpath.str);
	else
	{
		new_pwd = getcwd(NULL, 0);
		if (new_pwd != NULL)
			var_set("PWD", new_pwd);
		free(new_pwd);
	}
	string_shutdown(&curpath);
	return (0);
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
	while ((ret = ft_getopt(av, "PL", &opt)) != -1)
	{
		if (ret == '?' || ret == ':')
		{
			ft_dprintf(2, "%s: unknown option -%c\n", av[0], opt.unknown_opt);
			return (1);
		}
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
	return (cd(dir, home, pwd, p));
}
