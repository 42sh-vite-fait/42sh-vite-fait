#include <assert.h>
#include "var.h"

extern t_var_priv		g_variables;
extern t_var_priv		g_environ_priv;
extern char				**g_environ;

t_var_priv	g_variables;
t_var_priv	g_environ_priv;
char		**g_environ;

void	var_init_with_environ(char **environ)
{
	ssize_t	equal_sign;

	assert(environ != NULL);
	var_init();
	while (*environ)
	{
		equal_sign = ft_strchrpos(*environ, '=');
		if (equal_sign == -1)
			var_set(*environ, "", VAR_ATTR_EXPORT);
		else
		{
			environ[0][equal_sign] = '\0';
			var_set(*environ, *environ + equal_sign + 1, VAR_ATTR_EXPORT);
			environ[0][equal_sign] = '=';
		}
		environ += 1;
	}
}

void	var_init(void)
{
	char		*null;

	null = NULL;
	fatal_malloc(array_init(&g_variables, sizeof(t_var)));
	fatal_malloc(array_init(&g_environ_priv, sizeof(char *)));
	fatal_malloc(array_push(&g_environ_priv, &null));
	g_environ = g_environ_priv.data;
}
