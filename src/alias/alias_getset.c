#include <stdbool.h>
#include <stdint.h>
#include "alias.h"
#include "string_42.h"
#include "array_42.h"

extern t_alias	g_alias;

static ssize_t	alias_position(const char *name, size_t len)
{
	size_t		left;
	size_t		right;
	size_t		mid;
	int			cmp;

	left = 0;
	right = g_alias.aliases.len - 1;
	while (left <= right && right < g_alias.aliases.len)
	{
		mid = (left + right) / 2;
		cmp = ft_strncmp(name,
				((t_string*)array_get_at(&g_alias.aliases, mid))->str, len);
		if (cmp == 0)
			return ((ssize_t)mid);
		else if (cmp < 0)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return (-1);
}

static size_t	insert_alias(const char *name, size_t len)
{
	bool		is_found;
	size_t		left;
	size_t		right;
	size_t		mid;
	int			cmp;

	if (g_alias.aliases.len == 0)
		return (0);
	cmp = 0;
	left = 0;
	is_found = false;
	right = g_alias.aliases.len - 1;
	while (is_found == false && left <= right && right < g_alias.aliases.len)
	{
		mid = (left + right) / 2;
		cmp = ft_strncmp(name,
				((t_string*)array_get_at(&g_alias.aliases, mid))->str, len);
		if (cmp == 0)
			is_found = true;
		else if (cmp < 0)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return (left);
}

const char		*alias_get_value(const t_string *name)
{
	const t_string	*name_value;
	ssize_t			index;

	if ((index = alias_position(name->str, name->len)) != -1)
	{
		name_value = array_get_at(&g_alias.aliases, (size_t)index);
		return (name_value->str + name->len + 1);
	}
	return (NULL);
}

int				alias_set(t_string *name_value)
{
	t_string	rm;
	size_t		insert;
	ssize_t		index;
	ssize_t		len;

	if ((len = ft_strnchrpos(name_value->str, '=', name_value->len)) < 1)
		return (-1);
	if ((index = alias_position(name_value->str, (size_t)len)) != -1)
	{
		if (!array_replace_at(&g_alias.aliases, (size_t)index, name_value, &rm))
			return (-1);
		string_shutdown(&rm);
		return (0);
	}
	insert = insert_alias(name_value->str, (size_t)len);
	if (array_insert_at(&g_alias.aliases, insert, name_value) == NULL)
		return (-1);
	return (0);
}

int				alias_unset(const t_string *name)
{
	t_string	removed;
	ssize_t		index;

	if ((index = alias_position(name->str, name->len)) != -1)
	{
		array_remove_at(&g_alias.aliases, (size_t)index, &removed);
		string_shutdown(&removed);
		return (0);
	}
	return (-1);
}
