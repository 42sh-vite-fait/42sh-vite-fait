#include <assert.h>
#include "errors.h"
#include "string_42.h"

#define ERROR			(-1)
#define NO_MORE_PATH	(0)
#define PATH_FOUND 		(1)
#define CMD_NOT_EXEC 	(126)
#define CMD_NOT_FOUND	(127)

static ssize_t	get_next_path_len(const char *paths)
{
	ssize_t	len;

	if (*paths == '\0')
		return (-1);
	len = ft_strchrpos(paths, ':');
	if (len == -1)
		return (ft_strlen(paths));
	else
		return (len);
}

static int	get_next_path(t_string *str, char const **paths, char const *name)
{
	ssize_t		len;

	if ((len = get_next_path_len(*paths)) == -1)
		return (NO_MORE_PATH);
	string_truncate(str, 0);
	string_reserve(str, len + ft_strlen(name) + 2);
	if (len == 0)
		string_nreplace(str, "./", 2);
	else
		string_nreplace(str, *paths, len);
	*paths += len;
	if (**paths == ':')
		*paths += 1;
	if (access(str->str, F_OK) != -1)
	{
		if (str->str[str->len - 1] != '/')
			string_cat(str, "/");
		string_cat(str, name);
		return (PATH_FOUND);
	}
	return (ERROR);
}

static int	try_exec_path(const char *paths, char * const *av,
		char * const *envp)
{
	t_string	test;
	int			error;
	int			ret;

	string_init(&test);
	error = CMD_NOT_FOUND;
	while ((ret = get_next_path(&test, &paths, av[0])) != NO_MORE_PATH)
	{
		if (ret == ERROR)
			continue ;
		if (execve(test.str, av, envp) == -1 && errno != ENOENT)
			error = errno;
	}
	if (error != CMD_NOT_FOUND)
		error_set_context("%s: %s", strerror(error), av[0]);
	else
		error_set_context("command not found: %s", av[0]);
	string_shutdown(&test);
	return (ERROR);
}

int			exec_with_path(const char *paths, char * const *av,
		char * const *envp)
{
	assert(paths != NULL);
	assert(av != NULL);
	assert(av[0] != NULL);
	assert(envp != NULL);
	if (ft_strchr(av[0], '/') != NULL)
	{
		execve(av[0], av, envp);
		error_set_context("%s: %s", strerror(errno), av[0]);
		ret = CMD_NOT_EXEC;
	}
	else
		ret = try_exec_path(paths, av, envp);
	error_print("execution");
	_exit(ret);
}
