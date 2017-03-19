#include <assert.h>
#include "str_42.h"
#include "array_42.h"
#include "var.h"
#include "errors.h"
#include "misc.h"

extern t_array	g_environ;

static ssize_t	get_entry_index(const char *name, size_t name_len)
{
	char	*entry;
	size_t	i;

	i = 0;
	while (i < g_environ.len)
	{
		entry = *(char**)array_get_at(&g_environ, i);
		if (entry == NULL)
			break ;
		if (!ft_strncmp(entry, name, name_len) && entry[name_len] == '=')
			return (i);
		i += 1;
	}
	return (-1);
}

int				var_get(const char *name, const char **value)
{
	void	*entry;
	ssize_t	entry_index;
	size_t	name_len;

	name_len = ft_strlen(name);
	assert(is_valid_name(name, name_len));
	entry_index = get_entry_index(name, name_len);
	if (entry_index == -1)
	{
		*value = NULL;
		return (ERROR_);
	}
	entry = *(char**)array_get_at(&g_environ, entry_index);
	*value = ft_strchr(entry, '=');
	if (*value == NULL)
		*value = "";
	else
		*value += 1;
	return (OK_);
}

char * const	*var_get_environ(void)
{
	return ((char * const *)g_environ.data);
}
