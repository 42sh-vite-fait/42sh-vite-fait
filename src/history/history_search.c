#include <stdlib.h>
#include <stdbool.h>
#include "history.h"
#include "cbuffer_42.h"
#include "string_42.h"

bool		history_search(t_result *ret, t_history const *h, const char *patt)
{
	size_t		i;
	const char	*command;
	const char	*match;

	i = h->cbuffer.len - 1;
	while ((command = history_get_id(h, i)) != NULL)
	{
		if ((match = ft_strrstr(command, patt)) != NULL)
		{
			if (ret != NULL)
			{
				ret->command_id = h->last_id + i;
				ret->offset = (size_t)(match - command);
			}
			return (true);
		}
		--i;
	}
	return (false);
}

static bool	search_command_from(t_result *ret, t_history const *hist,
								const char *patt, t_result from)
{
	size_t		len;
	const char	*command;
	const char	*match;

	len = ft_strlen(patt);
	if (from.offset >= len && (command = history_get_id(hist, from.command_id)))
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

bool		history_search_from(t_result *ret, t_history const *history,
								const char *pattern, t_result from)
{
	size_t		i;
	const char	*command;
	const char	*match;

	if (history_contains(history, from.command_id) == false)
		return (false);
	if (search_command_from(ret, history, pattern, from) == true)
		return (true);
	i = from.command_id + 1;
	while ((command = history_get_id(history, i)) != NULL)
	{
		if ((match = ft_strrstr(command, pattern)) != NULL)
		{
			if (ret != NULL)
			{
				ret->command_id = history->last_id + i;
				ret->offset = (size_t)(match - command);
			}
			return (true);
		}
		--i;
	}
	return (false);
}
