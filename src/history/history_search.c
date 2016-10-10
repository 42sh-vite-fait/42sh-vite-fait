#include <stdlib.h>
#include <stdbool.h>
#include "history.h"
#include "cbuffer_42.h"
#include "string_42.h"

extern t_history	g_history;

bool		history_find(t_result *ret, const char *patt)
{
	size_t		i;
	const char	*command;
	const char	*match;
	size_t		i;

	i = g_history.last_id;
	while (i > g_history.last_id - g_history.cbuffer.len)
	{
		command = history_get_id(i);
		if ((match = ft_strrstr(command, patt)) != NULL)
		{
			if (ret != NULL)
			{
				ret->command_id = i;
				ret->offset = (size_t)(match - command);
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
	if (from.offset >= len && (command = history_get_id(from.command_id)))
	{
		if ((match = ft_strrnstr(command, patt, from.offset - 1)) != NULL)
		{
			ret->command_id = from.command_id;
			ret->offset = (size_t)(match - command);
			return (true);
		}
	}
	return (false);
}

bool		history_find_from(t_result *ret, const char *pattern, t_result from)
{
	size_t		i;
	const char	*command;
	const char	*match;
	size_t		i;

	if (history_contains(from.command_id) == false)
		return (false);
	if (search_command_from(ret, pattern, from) == true)
		return (true);
	i = from.command_id - 1;
	while (i > from.command_id - g_history.cbuffer.len - 1)
	{
		command = history_get_id(i);
		if ((match = ft_strrstr(command, pattern)) != NULL)
		{
			if (ret != NULL)
			{
				ret->command_id = i;
				ret->offset = (size_t)(match - command);
			}
			return (true);
		}
		--i;
	}
	return (false);
}

bool		history_find_start_with(t_result *ret, const char *pattern)
{
	size_t		pattern_len;
	const char	*command;
	size_t		i;

	i = g_history.last_id;
	while (i > g_history.last_id - g_history.cbuffer.len)
	{
		command = history_get_id(i);
		pattern_len = ft_strlen(pattern);
		// TODO use strncmp when created
		if (ft_strnstr(command, pattern, pattern_len) != NULL)
		{
			if (ret != NULL)
			{
				ret->command_id = i;
				ret->offset = 0;
			}
			return (true);
		}
		--i;
	}
	return (false);
}
