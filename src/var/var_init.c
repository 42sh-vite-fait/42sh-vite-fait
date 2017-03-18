#include <assert.h>
#include "array_42.h"
#include "var.h"

t_array	g_environ;

void	var_init(char **environ)
{
	char	*str;

	assert(environ != NULL);
	fatal_malloc(array_init(&g_environ, sizeof(char*)));
	while (*environ)
	{
		str = ft_strdup(*environ);
		fatal_malloc(array_push(&g_environ, &str));
		environ += 1;
	}
	str = NULL;
	fatal_malloc(array_push(&g_environ, &str));
}

void	var_shutdown(void)
{
	var_clear();
	array_shutdown(&g_environ);
}

void	var_clear(void)
{
	void	*ptr;

	while (g_environ.len)
	{
		array_pop(&g_environ, &ptr);
		free(ptr);
	}
	ptr = NULL;
	fatal_malloc(array_push(&g_environ, &ptr));
}
