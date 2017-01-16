#include "var.h"
#include "errors.h"
#include "array_42.h"
#include "misc.h"

extern t_var_priv	g_variables;

static int	match_var_by_name(const void *var, const void *name)
{
	return (!ft_strcmp(((t_var*)var)->name, name));
}

int			var_get(const char *name, const char **value)
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
		return (NO_ERROR);
	}
	*value = NULL;
	return (ERR_VAR_NOT_FOUND);
}
