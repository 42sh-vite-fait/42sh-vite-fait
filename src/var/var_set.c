#include "errors.h"
#include "var.h"
#include "misc.h"

extern t_var_priv	g_environ_priv;
extern t_var_priv	g_variables;
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

static void	set_environ_entry(t_var *var)
{
	t_string	buf;

	fatal_malloc(string_init(&buf));
	fatal_malloc(string_cat(&buf, var->name));
	fatal_malloc(string_cat(&buf, "="));
	fatal_malloc(string_cat(&buf, var->value));
	fatal_malloc(array_insert_at(&g_environ_priv,
				g_environ_priv.len - 1, &(buf.str)));
	g_environ = g_environ_priv.data;
}

static void	remove_environ_entry(const char *name)
{
	void	*elem;

	elem = array_find(g_environ_priv, &match_env_var_by_name, name);
	free(*((char**)elem));
	array_remove_elem(&g_environ_priv, elem);
	g_environ = g_environ_priv.data;
}

int			var_set(const char *name, const char *value, int attrs)
{
	t_var	*var;

	if (!is_valid_name(name, ft_strlen(name)))
		return (ERR_VAR_BAD_NAME);
	if ((var = array_find(g_variables, &match_var_by_name, name)) == NULL)
	{
		var = fatal_malloc(array_get_available(&g_variables));
		var->name = fatal_malloc(ft_strdup(name));
		var->value = NULL;
		var->attrs = 0U;
	}
	if (value != NULL && var->attrs & VAR_ATTR_RDONLY)
		return (ERR_VAR_RDONLY);
	if (var->attrs & VAR_ATTR_EXPORT && var->value != NULL)
		remove_environ_entry(name);
	if (value)
	{
		free(var->value);
		var->value = fatal_malloc(ft_strdup(value));
	}
	var->attrs |= attrs;
	if (var->attrs & VAR_ATTR_EXPORT && var->value != NULL)
		set_environ_entry(var);
	return (VAR_OK_);
}
