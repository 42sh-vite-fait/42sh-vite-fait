#include "var.h"

extern t_var_priv		g_variables;
extern t_var_priv		g_environ_priv;
extern char				**g_environ;

t_var_priv	g_variables;
t_var_priv	g_environ_priv;
char		**g_environ;

void	var_init(void)
{
	char	*null;

	null = NULL;
	fatal_malloc(array_init(&g_variables, sizeof(t_var)));
	fatal_malloc(array_init(&g_environ_priv, sizeof(char *)));
	fatal_malloc(array_push(&g_environ_priv, &null));
	g_environ = g_environ_priv.data;
}
