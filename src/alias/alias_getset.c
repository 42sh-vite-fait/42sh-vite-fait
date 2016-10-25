#include "alias.h"

extern t_alias	g_alias;

static ssize_t		alias_get_index(const char *name, size_t len)
{
	int				cmp;
	size_t			l;
	size_t			r;
	ssize_t			m;

	if (g_alias.aliases.len == 0)
		return (-1);
	l = 0;
	r = g_alias.aliases.len - 1;
	while (l <= r)
	{
		m = (l + r) / 2;
		cmp = ft_strncmp(name, array_get_at(g_alias.aliases, m)->str, len);
		if (cmp < 0)
			l = m + 1;
		else if (cmp > 0)
			r = m - 1;
		else
			return (m);
	}
	return (-1);
}

const char			*alias_get(const t_string *name)
{
	ssize_t		index;

	index = alias_get_index(name->str, name->len);
	if (index != -1)
	{
		return (array_get_at(g_alias.aliases, (size_t)index) + name->len + 2);
	}
	return (NULL);
}

int					alias_set(t_string *name_value)
{
	ssize_t			equal_pos;
	const t_string	*removed;
	int				cmp;
	size_t			l;
	size_t			r;
	ssize_t			m;

	if (g_alias.aliases.len == 0)
		return (-1);
	l = 0;
	r = g_alias.aliases.len - 1;
	equal_pos = ft_strchrpos(name_value->str, '=');
	while (l <= r)
	{
		m = (l + r) / 2;
		cmp = ft_strncmp(name, array_get_at(g_alias.aliases, m)->str, len);
		if (cmp < 0)
			l = m + 1;
		else if (cmp > 0)
			r = m - 1;
		else
		{
			array_replace_at(&g_alias.aliases, m, name_value, removed);
			string_shutdown(removed);
			return (0);
		}
	}
	return (-(array_insert_at(&g_alias.aliases, m, name_value) == NULL));
}

int					alias_unset(const t_string *name)
{
	ssize_t		index;

	index = alias_get_index(name->str, name->len);
	if (index != -1)
	{
		array_remove_at(g_alias.aliases, (size_t)index);
		return (0);
	}
	return (-1);
}
