#include "var.h"
#include "errors.h"
#include "array_42.h"
#include "misc.h"

extern t_var_priv	g_variables;
extern char			**g_environ;

static int		match_var_by_name(const void *var, const void *name)
{
	return (!ft_strcmp(((t_var*)var)->name, name));
}

int				var_get(const char *name, const char **value)
{
	void	*match;

	if (!is_valid_name(name, ft_strlen(name)))
	{
		*value = NULL;
		return (ERR_VAR_BAD_NAME);
	}
	match = array_find(g_variables, &match_var_by_name, name);
	if (match)
	{
		*value = ((t_var*)match)->value;
		return (VAR_OK_);
	}
	*value = NULL;
	return (ERR_VAR_NOT_FOUND);
}

char * const	*var_get_environ(void)
{
	return ((char * const *)g_environ);
}
