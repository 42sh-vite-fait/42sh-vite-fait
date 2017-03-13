#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "builtins.h"
#include "str_42.h"
#include "exit_status.h"

#define ARRAY_ELEMS(A)	(sizeof(A) / sizeof(A[0]))

t_pair_name_builtin	g_builtins[] =
{
//	{"cd", NULL},
	{"echo", &builtin_echo},
	{"env", &builtin_env},
	{"exit", &builtin_exit},
//	{"getenv", NULL},
	{"history", &builtin_history},
//	{"pwd", NULL},
	{"setenv", &builtin_setenv},
	{"unsetenv", &builtin_unsetenv},
};

const size_t		g_builtins_len = ARR_SIZ_MAX(g_builtins);

static int	find_builtin_id(char const *name, size_t len)
{
	size_t	i;
	int		diff;

	i = 0;
	assert(name != NULL);
	while (i < g_builtins_len)
	{
		diff = ft_strncmp(name, g_builtins[i].name, len);
		if (diff == 0 && g_builtins[i].name[len] == '\0')
			return ((int)i);
		i += 1;
	}
	return (-1);
}

bool		is_builtin(const char *name, size_t len)
{
	return (find_builtin_id(name, len) != -1);
}

int			exec_builtin(int ac, const char *const *av)
{
	int		id;
	int	exit_status;

	id = find_builtin_id(av[0], ft_strlen(av[0]));
	assert(id != -1);
	exit_status = g_builtins[id].builtin(ac, av);
	exit_status_set_last(exit_status);
	return (exit_status);
}
