#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include "memory_42.h"
#include "errors.h"

typedef int					t_builtin(int, const char * const *);

typedef union u_command		t_command;
typedef struct s_pair_name_builtin	t_pair_name_builtin;

union	u_command
{
	const char	*path;
	t_builtin	*builtin;
};

struct	s_pair_name_builtin
{
	char		*name;
	t_builtin	*builtin;
};

#define ERROR			-1

#define ARRAY_ELEMS(A)	(sizeof(A) / sizeof(A[0]))

static t_pair_name_builtin		g_builtins[] =
{
	{"cd", (t_builtin *)1},
	{"fc", (t_builtin *)2},
	{"getopts", (t_builtin *)3},
	{"pwd", (t_builtin *)4},
	{"read", (t_builtin *)5},
};

static int	are_builtins_sorted()
{
	size_t	i;

	i = 0;
	while (i + 1 < ARRAY_ELEMS(g_builtins))
	{
		if (ft_strcmp(g_builtins[i].name, g_builtins[i + 1].name) > 0)
			return (0);
		i += 1;
	}
	return (1);
}

static int	get_next_path(t_string *str, char const **path, char const *name)
{
	const char	*path_end;

	if (**path == '\0')
		return (0);
	path_end = ft_strchr(*path, ':');
	if (path_end == NULL)
		path_end = ft_strchr(*path, '\0');
	string_truncate(str, 0);
	string_reserve(str, (unsigned long)(path_end - *path) + ft_strlen(name) + 2);
	if (path_end - *path == 0)
		string_nreplace(str, "./", 2);
	else
		string_nreplace(str, *path, (size_t)(path_end - *path));
	*path = path_end;
	if (**path == ':')
		*path += 1;
	if (access(str->str, F_OK) != -1)
	{
		if (str->str[str->len - 1] != '/')
			string_cat(str, "/");
		string_cat(str, name);
		return (1);
	}
	return (ERROR);
}

int		try_exec_path(const char *name, const char *path,
					char * const av[], char * const envp[])

{
	t_string	test;
	int			error;
	int			ret;

	string_init(&test);
	error = 0;
	while ((ret = get_next_path(&test, &path, name)) != 0)
	{
		if (ret != ERROR)
			if (execve(test.str, av, envp) == -1 && errno != ENOENT)
				error = errno;
	}
	if (error != 0)
		error_set_context("%s: %s", strerror(error), name);
	else
		error_set_context("command not found: %s", name);
	string_shutdown(&test);
	return (ERROR);
}

/*
  such dychotomy
  never ask me how it works...
*/
t_builtin	*find_builtin(char const *name)
{
	size_t	min;
	size_t	max;
	size_t	i;
	int		diff;

	min = 0;
	max = ARRAY_ELEMS(g_builtins);
	assert(name != NULL);
	assert(are_builtins_sorted());
	while (min != max)
	{
		i = min + (max - min) / 2;
		diff = ft_strcmp(name, g_builtins[i].name);
		if (diff == 0)
			return (g_builtins[i].builtin);
		else if (diff > 0)
			min += (max - min + 1) / 2;
		else
			max -= (max - min + 1) / 2;
	}
	return (NULL);
}

int			exec_binary(char const *name, char const *paths,
						char * const av[], char * const envp[])
{
	assert(name != NULL);
	assert(paths != NULL);
	assert(av != NULL);
	assert(envp != NULL);
	if (ft_strchr(name, '/') != NULL)
	{
		execve(name, av, envp);
		error_set_context("%s: %s", strerror(errno), name);
	}
	else
		try_exec_path(name, paths, av, envp);
	error_print("");
	_exit(1);
}
