#include <stdbool.h>
#include <stdint.h>
#include "alias.h"
#include "array_42.h"

extern t_alias	g_alias;

static bool		is_alias_present(const char *name, size_t len, size_t *index)
{
	size_t		left;
	size_t		right;
	size_t		mid;
	int			cmp;

	left = 0;
	right = g_alias.len - 1;
	while (left <= right && right < g_alias.len)
	{
		mid = (left + right) / 2;
		cmp = ft_strncmp(name, *(char**)array_get_at(&g_alias, mid), len);
		if (cmp == 0)
		{
			*index = mid;
			return (true);
		}
		else if (cmp < 0)
			left = mid + 1;
		else if (cmp > 0)
			right = mid - 1;
	}
	*index = left;
	return (false);
}

const char		*alias_get_value(const char *name)
{
	const char	*name_value;
	size_t		name_len;
	size_t		index;

	name_len = ft_strlen(name);
	if (is_alias_present(name, name_len, &index) == true)
	{
		name_value = *(char**)array_get_at(&g_alias, index);
		return (name_value + name_len + 1);
	}
	return (NULL);
}

int				alias_set(char *name_value)
{
	char		*rm;
	ssize_t		len;
	size_t		index;
	size_t		name_value_len;

	name_value_len = ft_strlen(name_value);
	if ((len = ft_strnchrpos(name_value, '=', name_value_len)) < 1)
		return (-1);
	if (is_alias_present(name_value, (size_t)len, &index) == true)
	{
		if (array_replace_at(&g_alias, index, &name_value, &rm) == NULL)
			return (-1);
		free(rm);
	}
	else
	{
		if (array_insert_at(&g_alias, index, &name_value) == NULL)
			return (-1);
	}
	return (0);
}

int				alias_unset(const char *name)
{
	char		*removed;
	size_t		index;
	size_t		name_len;

	name_len = ft_strlen(name);
	if (is_alias_present(name, name_len, &index) == true)
	{
		array_remove_at(&g_alias, index, &removed);
		free(removed);
		return (0);
	}
	return (-1);
}
