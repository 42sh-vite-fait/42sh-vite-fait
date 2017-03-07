#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "builtins.h"
#include "str_42.h"
#include "exit_status.h"

#define ARRAY_ELEMS(A)	(sizeof(A) / sizeof(A[0]))

/*
** These shall be sorted
*/
t_pair_name_builtin	g_builtins[] =
{
	{"cd", NULL},
	{"echo", &builtin_echo},
	{"exit", &builtin_exit},
	{"getenv", NULL},
	{"pwd", NULL},
	{"setenv", NULL},
};
const size_t		g_builtins_nb = sizeof(g_builtins) / sizeof(g_builtins[0]);

#ifndef NDEBUG

static int	are_builtins_sorted(void)
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

#endif

static int	find_builtin_id(char const *name, size_t len)
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
		diff = ft_strncmp(name, g_builtins[i].name, len);
		if (diff == 0)
			return ((int)i);
		else if (diff > 0)
			min += (max - min + 1) / 2;
		else
			max -= (max - min + 1) / 2;
	}
	return (-1);
}

bool		is_builtin(const char *name, size_t len)
{
	return (find_builtin_id(name, len) != -1);
}

int			exec_builtin(int ac, char *const *av, char *const *env)
{
	int		id;
	int	exit_status;

	id = find_builtin_id(av[0], ft_strlen(av[0]) + 1);
	assert(id != -1);
	exit_status = g_builtins[id].builtin(ac, av, env);
	exit_status_set_last(exit_status);
	return (exit_status);
}
