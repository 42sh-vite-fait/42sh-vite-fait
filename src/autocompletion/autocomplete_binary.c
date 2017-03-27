#include <assert.h>
#include <dirent.h>
#include "errors.h"
#include "string_42.h"
#include "autocompletion.h"
#include "misc.h"
#include "array_42.h"

static bool	is_dot_or_dot_dot_file(const char *f)
{
	return (f[0] == '.' && (f[1] == '\0' || (f[1] == '.' && f[2] == '\0')));
}

static void	find_in_path(t_array *matches, const char *path, const char *name,
						const char *prefix)
{
	DIR				*d;
	struct dirent	*current;
	t_string		found;
	size_t			name_len;
	size_t			prefix_len;

	name_len = ft_strlen(name);
	prefix_len = ft_strlen(prefix);
	d = opendir(path);
	if (d == NULL)
		return ;
	while ((current = readdir(d)) != NULL)
	{
		if (ft_strncmp(name, current->d_name, name_len) == 0 &&
			!is_dot_or_dot_dot_file(current->d_name))
		{
			fatal_malloc(string_init_ndup(&found, prefix, prefix_len));
			fatal_malloc(string_cat(&found, current->d_name));
			fatal_malloc(array_push(matches, &found.str));
		}
	}
	closedir(d);
}

void		complete_cmd_in_paths(t_array *matches, const char *name,
								const char *paths)
{
	t_string	test;

	string_init(&test);
	while ((paths = get_next_path(&test, paths)) != NULL)
		find_in_path(matches, test.str, name, "");
	string_shutdown(&test);
}

void		complete_cmd_in_pwd(t_array *matches, const char *cmd,
								const char *pwd)
{
	find_in_path(matches, pwd, cmd, "");
	return ;
}

void		complete_path(t_array *matches, const char *path)
{
	t_string	dir;
	t_string	file;
	ssize_t		dir_len;
	size_t		path_len;

	path_len = ft_strlen(path);
	dir_len = ft_strrchrpos(path, '/');
	if (dir_len == -1)
		return ;
	dir_len += 1;
	fatal_malloc(string_init_ndup(&dir, path, dir_len));
	fatal_malloc(string_init_ndup(&file, path + dir_len, path_len - dir_len));
	find_in_path(matches, dir.str, file.str, dir.str);
	string_shutdown(&file);
}
