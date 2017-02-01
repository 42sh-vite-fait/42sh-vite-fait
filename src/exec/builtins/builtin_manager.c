#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "builtins.h"
#include "str_42.h"

#define ARRAY_ELEMS(A)	(sizeof(A) / sizeof(A[0]))

/*
** These shall be sorted
*/
static t_pair_name_builtin		g_builtins[] =
{
	{"cd", NULL},
	{"echo", NULL},
	{"getenv", NULL},
	{"pwd", NULL},
	{"setenv", NULL},
};

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

const char	*complete_builtin_name(const char *name, size_t len)
{
	int		id;

	id = find_builtin_id(name, len);
	if (id != -1)
		return (g_builtins[id].name);
	return (NULL);
}

int			exec_builtin(int ac, char *const *av, char *const *env)
{
	int		id;

	id = find_builtin_id(av[0], ft_strlen(av[0]) + 1);
	assert(id != -1);
	return (g_builtins[id].builtin(ac, av, env));
}
