#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "str_42.h"

#define ARRAY_ELEMS(A)	(sizeof(A) / sizeof(A[0]))

typedef int					t_builtin(int, const char * const *);

typedef struct s_pair_name_builtin	t_pair_name_builtin;

struct	s_pair_name_builtin
{
	char		*name;
	t_builtin	*builtin;
};


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

int	exec_builtin(const char *paths, char * const *av, char * const *envp)
{
	// recupere l'index du builtin
	// call le builtin
	// retourne l'exit code du builtin
	(void)paths;
	(void)av;
	(void)envp;
	return (-1);
}

bool is_builtin(const char *cmd, size_t	len)
{
	(void)cmd;
	(void)len;
	return (false);
}
