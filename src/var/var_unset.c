#include "var.h"
#include "errors.h"

extern t_var_priv	g_variables;
extern t_var_priv	g_environ_priv;
extern char			**g_environ;

static int	match_var_by_name(const void *var, const void *name)
{
	return (!ft_strcmp(((t_var*)var)->name, name));
}

static int	match_env_var_by_name(const void *env_var, const void *name)
{
	size_t	len;

	if (*((char**)env_var) == NULL)
		return (0);
	len = ft_strlen((char*)name);
	if (ft_strncmp(*((char**)env_var), (char*)name, len) == 0)
		if ((*((char**)env_var))[len] == '=')
			return (1);
	return (0);
}

static void	remove_environ_entry(const char *name)
{
	void	*elem;

	elem = array_find(g_environ_priv, &match_env_var_by_name, name);
	free(*((char**)elem));
	array_remove_elem(&g_environ_priv, elem);
	g_environ = g_environ_priv.data;
}

int			var_unset(char const *name)
{
	t_var	*match;

	match = array_find(g_variables, &match_var_by_name, name);
	if (match == NULL)
		return (ERR_VAR_NOT_FOUND);
	if (match->attrs & VAR_ATTR_RDONLY)
		return (ERR_VAR_RDONLY);
	free(match->value);
	free(match->name);
	if (match->attrs & VAR_ATTR_EXPORT && match->value != NULL)
		remove_environ_entry(name);
	array_remove_elem(&g_variables, match);
	return (NO_ERROR);
}
