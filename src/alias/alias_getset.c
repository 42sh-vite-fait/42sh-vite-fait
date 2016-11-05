#include <stdbool.h>
#include <stdint.h>
#include "alias.h"
#include "string_42.h"
#include "array_42.h"

#define ARRAY_GET_STR(m) (((t_string*)array_get_at(&g_alias, m))->str)

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
		cmp = ft_strncmp(name, ARRAY_GET_STR(mid), len);
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
	const t_string	*name_value;
	size_t			name_len;
	size_t			index;

	name_len = ft_strlen(name);
	if (is_alias_present(name, name_len, &index) == true)
	{
		name_value = array_get_at(&g_alias, index);
		return (name_value->str + name_len + 1);
	}
	return (NULL);
}

int				alias_set(char *name_value)
{
	t_string	rm;
	ssize_t		len;
	size_t		index;
	size_t		name_value_len;

	name_value_len = ft_strlen(name_value);
	if ((len = ft_strnchrpos(name_value, '=', name_value_len)) < 1)
		return (-1);
	if (is_alias_present(name_value, (size_t)len, &index) == true)
	{
		// TODO use string_construct_from(char *str, size_t len, size_t capacity);
		t_string name_value_string = (t_string){ .str = name_value, .len = name_value_len, .capacity = name_value_len };

		if (array_replace_at(&g_alias, index, &name_value_string, &rm) == NULL)
			return (-1);
		string_shutdown(&rm);
	}
	else
	{
		// TODO use string_construct_from(char *str, size_t len, size_t capacity);
		t_string name_value_string = (t_string){ .str = name_value, .len = name_value_len, .capacity = name_value_len };

		if (array_insert_at(&g_alias, index, &name_value_string) == NULL)
			return (-1);
	}
	return (0);
}

int				alias_unset(const char *name)
{
	t_string	removed;
	size_t		index;
	size_t		name_len;

	name_len = ft_strlen(name);
	if (is_alias_present(name, name_len, &index) == true)
	{
		array_remove_at(&g_alias, index, &removed);
		string_shutdown(&removed);
		return (0);
	}
	return (-1);
}
