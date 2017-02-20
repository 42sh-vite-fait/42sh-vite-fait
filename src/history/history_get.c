#include <stdlib.h>
#include "history.h"
#include "cbuffer_42.h"
#include "str_42.h"

extern t_history	g_history;

const t_string		*history_get(size_t id)
{
	const t_string	*command_ptr;
	size_t			bid;

	if (id <= g_history.last_id
		&& id > g_history.last_id - g_history.commands.len)
	{
		bid = g_history.commands.len - g_history.last_id + id - 1;
		command_ptr = (const t_string*)cbuffer_get_at(&g_history.commands, bid);
		return (command_ptr);
	}
	return (NULL);
}

size_t				history_get_last_str_id(const char *str)
{
	size_t			i;
	size_t			end;
	const t_string	*history_entry;
	size_t			str_len;

	str_len = ft_strlen(str);
	end = history_get_last_id();
	i = history_get_first_id();
	while (i <= end)
	{
		history_entry = history_get(i);
		if (ft_strncmp(history_entry->str, str, str_len) == 0)
			return (i);
		i++;
	}
	return (0);
}

size_t				history_get_last_id(void)
{
	return (g_history.last_id);
}

size_t				history_get_first_id(void)
{
	return (g_history.last_id - g_history.commands.len + 1);
}
