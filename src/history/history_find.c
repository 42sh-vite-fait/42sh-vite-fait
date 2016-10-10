#include <stdlib.h>
#include <stdbool.h>
#include "history.h"
#include "cbuffer_42.h"
#include "string_42.h"

extern t_history	g_history;

bool		history_find(t_result *ret, const char *pattern)
{
	const char	**command_ptr;
	const char	*match;
	size_t		i;

	i = g_history.cbuffer.len;
	while (i > 0)
	{
		command_ptr = cbuffer_at(&g_history.cbuffer, i - 1);
		if ((match = ft_strrstr(*command_ptr, pattern)) != NULL)
		{
			if (ret != NULL)
			{
				ret->command_id = g_history.last_id - g_history.cbuffer.len + i;
				ret->offset = (size_t)(match - *command_ptr);
			}
			return (true);
		}
		--i;
	}
	return (false);
}

static bool	search_command_from(t_result *ret, const char *patt, t_result from)
{
	size_t		len;
	const char	*command;
	const char	*match;
	size_t		len;

	len = ft_strlen(patt);
	if (from.offset >= len && (command = history_get(from.command_id)))
	{
		if ((match = ft_strrnstr(command, patt, from.offset - 1)) != NULL)
		{
			if (ret != NULL)
			{
				ret->command_id = from.command_id;
				ret->offset = (size_t)(match - command);
			}
			return (true);
		}
	}
	return (false);
}

bool		history_find_from(t_result *ret, const char *pattern, t_result from)
{
	const char	**command_ptr;
	const char	*match;
	size_t		i;

	if (HIST_CONTAINS(g_history, from.command_id) == false)
		return (false);
	if (search_command_from(ret, pattern, from) == true)
		return (true);
	i = g_history.cbuffer.len - g_history.last_id + from.command_id - 1;
	while (i > 0)
	{
		command_ptr = cbuffer_at(&g_history.cbuffer, i - 1);
		if ((match = ft_strrstr(*command_ptr, pattern)) != NULL)
		{
			if (ret != NULL)
			{
				ret->command_id = g_history.last_id - g_history.cbuffer.len + i;
				ret->offset = (size_t)(match - *command_ptr);
			}
			return (true);
		}
		--i;
	}
	return (false);
}

bool		history_find_start_with(t_result *ret, const char *pattern)
{
	const char	**command_ptr;
	size_t		pattern_len;
	size_t		i;

	i = g_history.cbuffer.len;
	while (i > 0)
	{
		command_ptr = cbuffer_at(&g_history.cbuffer, i - 1);
		pattern_len = ft_strlen(pattern);
		// TODO use strncmp when created
		if (ft_strnstr(*command_ptr, pattern, pattern_len) != NULL)
		{
			if (ret != NULL)
			{
				ret->command_id = g_history.last_id - g_history.cbuffer.len + i;
				ret->offset = 0;
			}
			return (true);
		}
		--i;
	}
	return (false);
}
