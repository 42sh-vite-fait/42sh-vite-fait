#include <stdlib.h>
#include <stdbool.h>
#include "history.h"
#include "cbuffer_42.h"
#include "string_42.h"

extern t_history	g_history;

bool		history_find(t_result *r, const char *pattern)
{
	const t_string	*command_ptr;
	const char		*match;
	size_t			i;

	i = g_history.commands.len;
	while (i > 0)
	{
		command_ptr = cbuffer_at(&g_history.commands, i - 1);
		if ((match = ft_strrstr(command_ptr->str, pattern)) != NULL)
		{
			if (r != NULL)
			{
				r->command_id = g_history.last_id - g_history.commands.len + i;
				r->offset = (size_t)(match - command_ptr->str);
			}
			return (true);
		}
		--i;
	}
	return (false);
}

static bool	search_command_from(t_result *ret, const char *patt, t_result from)
{
	const t_string	*cmd_ptr;
	const char		*match;
	size_t			len;

	len = ft_strlen(patt);
	if (from.offset >= len && (cmd_ptr = history_get(from.command_id)))
	{
		if ((match = ft_strrnstr(cmd_ptr->str, patt, from.offset - 1)) != NULL)
		{
			if (ret != NULL)
			{
				ret->command_id = from.command_id;
				ret->offset = (size_t)(match - cmd_ptr->str);
			}
			return (true);
		}
	}
	return (false);
}

bool		history_find_from(t_result *r, const char *pattern, t_result from)
{
	const t_string	*command_ptr;
	const char		*match;
	size_t			i;

	if (search_command_from(r, pattern, from) == true)
		return (true);
	i = g_history.commands.len - g_history.last_id + from.command_id - 1;
	while (i > 0)
	{
		command_ptr = cbuffer_at(&g_history.commands, i - 1);
		if ((match = ft_strrstr(command_ptr->str, pattern)) != NULL)
		{
			if (r != NULL)
			{
				r->command_id = g_history.last_id - g_history.commands.len + i;
				r->offset = (size_t)(match - command_ptr->str);
			}
			return (true);
		}
		--i;
	}
	return (false);
}

bool		history_find_start_with(t_result *r, const char *pattern)
{
	const t_string	*command_ptr;
	size_t			pattern_len;
	size_t			i;

	i = g_history.commands.len;
	while (i > 0)
	{
		command_ptr = cbuffer_at(&g_history.commands, i - 1);
		pattern_len = ft_strlen(pattern);
		if (ft_strncmp(command_ptr->str, pattern, pattern_len) == 0)
		{
			if (r != NULL)
			{
				r->command_id = g_history.last_id - g_history.commands.len + i;
				r->offset = 0;
			}
			return (true);
		}
		--i;
	}
	return (false);
}
