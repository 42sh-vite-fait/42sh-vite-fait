#include "alias.h"
#include <stdbool.h>
#include <stdint.h>

extern t_alias	g_alias;

static bool		is_alias_present(const char *name, size_t len, size_t *last)
{
	int			cmp;
	size_t		l;
	size_t		r;
	size_t		m;

	if (g_alias.aliases.len == 0)
		return (-1);
	l = 0;
	m = 0;
	r = g_alias.aliases.len - 1;
	while (l <= r)
	{
		m = (l + r) / 2;
		cmp = ft_strncmp(name, ((t_string*)array_get_at(&g_alias.aliases, m))->str, len);
		if (cmp < 0)
			l = m + 1;
		else if (cmp > 0)
			r = m - 1;
		else
		{
			if (last != NULL)
				*last = m;
			return (true);
		}
	}
	if (last != NULL)
		*last = m;
	return (false);
}

const char		*alias_get(const t_string *name)
{
	size_t		index;

	if (is_alias_present(name->str, name->len, &index) == true)
	{
		return ((char*)array_get_at(&g_alias.aliases, index) + name->len + 2);
	}
	return (NULL);
}

int				alias_set(t_string *name_value)
{
	const t_string	*removed;
	size_t			index;

	if (is_alias_present(name->str, name->len, &index) == true)
	{
		if (array_replace_at(&g_alias.aliases, index, name_value, removed) == NULL)
			return (-1);
		string_shutdown(removed);
	}
	else if (array_insert_at(&g_alias.aliases, index, name_value) == NULL)
		return (-1);
	return (0);
}

int				alias_unset(const t_string *name)
{
	size_t		index;

	if (is_alias_present(name->str, name->len, &index) == true)
	{
		array_remove_at(&g_alias.aliases, index);
		return (0);
	}
	return (-1);
}
