#include <stdbool.h>
#include <stddef.h>
#include "var.h"
#include "string_42.h"
#include "misc.h"
#include "errors.h"

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

	tmp = curpath->str;
	prev_component = NULL;
	while (*tmp)
	{
		if (tmp[0] == '.' && (!tmp[1] || tmp[1] == '/'))
		{
			i = 1;
			while (tmp[1] == '/')
				i += 1;
			string_remove(curpath, tmp - curpath->str, i);
		}
		else if (tmp[0] == '.' && tmp[1] == '.' && (!tmp[2] || tmp[3] == '/') && prev_component != NULL)
		{
			tmp[-1] = '\0';
			if (!is_dir(curpath->str))
			{
				error_set_context("%s", strerror(errno));
				return (-1);
			}
			tmp[-1] = '/';
			i = 2;
			while (tmp[1] == '/')
				i += 1;
			string_remove(curpath, prev_component - curpath->str, tmp - prev_component + i);
			tmp = prev_component;
			if (prev_component == curpath->str)
				prev_component = NULL;
		}
		else
		{
			prev_component = tmp;
			while (*tmp && *tmp != '/')
				tmp += 1;
		}
	}
	return (0);
}

/*
** home, dir and pwd shall have a trailing slash character ('/')
*/
int		cd(const char *dir, const char *home, const char *pwd, bool P)
{
	t_string	curpath;
	t_string	comp;
	t_string	backup;
	bool		is_backup;

	string_init(&curpath);
	string_init(&comp);
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
		get_next_component(&comp, curpath.str);
		if (ft_strcmp(comp.str, ".") || ft_strcmp(comp.str, "..")) /* Rule 4 */
			string_cat(&curpath, dir); /* Rule 6 */
		else
			rule_5(&curpath, dir); /* Rule 5 + 6 */
	}
	if (!P) /* Rule 7 */
	{
		if (curpath.str[0] != '/')
			string_insert(&curpath, 0, pwd, ft_strlen(pwd));
		if (rule_8(&curpath) == -1) /* Rule 8 */
		{
			error_print("cd");
			return 1;
		}
		if (ft_strncmp(pwd, curpath.str, ft_strlen(dir))) /* Rule 9 */
		{
			//TODO: Replace by string_sub_replace()
			string_remove(&curpath, 0, ft_strlen(dir - 1));
			string_insert(&curpath, 0, ".", 1);
		}
		if (chdir(curpath.str) == -1) /* Rule 10 */
		{
			error_set_context("%d", strerror(errno));
			error_print("cd");
			return 1;
		}
	}
	return (0);
}
