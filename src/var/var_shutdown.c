#include "var.h"

extern t_var_priv	g_variables;
extern t_var_priv	g_environ_priv;

static void	free_environ_entry(void *entryptr)
{
	free(*((char**)entryptr));
}

static void	free_var_namenval(void *var)
{
	free(((t_var*)var)->name);
	free(((t_var*)var)->value);
}

static void	iter_array(t_array set, void (*func)(void *elem))
{
	size_t	n;

	n = 0;
	while (n < set.len)
		func(array_get_at(&set, n++));
}

void		var_shutdown(void)
{
	iter_array(g_variables, &free_var_namenval);
	iter_array(g_environ_priv, &free_environ_entry);
	array_shutdown(&g_variables);
	array_shutdown(&g_environ_priv);
}
