#include <stdlib.h>
#include <stdbool.h>
#include "history.h"
#include "cbuffer_42.h"
#include "string_42.h"

extern t_history	g_history;

bool		history_find(t_result *r, const char *pattern)
{
	const t_string	*cmd;
	const char		*match;
	size_t			i;

	i = g_history.commands.len;
	while (i > 0)
	{
		cmd = cbuffer_at(&g_history.commands, i - 1);
		if ((match = ft_strrstr(cmd->str, pattern)) != NULL)
		{
			if (r != NULL)
			{
				r->command_id = g_history.last_id - g_history.commands.len + i;
				r->offset = (size_t)(match - cmd->str);
			}
			return (true);
		}
		--i;
	}
	return (false);
}

static bool	search_command_from(t_result *ret, const char *patt, t_result from)
{
	const t_string	*cmd;
	const char		*match;

	if (from.offset >= ft_strlen(patt) && (cmd = history_get(from.command_id)))
	{
		if ((match = ft_strrnstr(cmd->str, patt, from.offset)) != NULL)
		{
			if (ret != NULL)
			{
				ret->command_id = from.command_id;
				ret->offset = (size_t)(match - cmd->str);
			}
			return (true);
		}
	}
	return (false);
}

bool		history_find_from(t_result *r, const char *pattern, t_result from)
{
	const t_string	*cmd;
	const char		*match;
	size_t			i;

	if (search_command_from(r, pattern, from) == true)
		return (true);
	i = g_history.commands.len - g_history.last_id + from.command_id - 1;
	while (i > 0)
	{
		cmd = cbuffer_at(&g_history.commands, i - 1);
		if ((match = ft_strrstr(cmd->str, pattern)) != NULL)
		{
			if (r != NULL)
			{
				r->command_id = g_history.last_id - g_history.commands.len + i;
				r->offset = (size_t)(match - cmd->str);
			}
			return (true);
		}
		--i;
	}
	return (false);
}

bool		history_find_start_with(t_result *r, const char *pattern)
{
	const t_string	*cmd;
	size_t			i;

	i = g_history.commands.len;
	while (i > 0)
	{
		cmd = cbuffer_at(&g_history.commands, i - 1);
		if (ft_strncmp(cmd->str, pattern, ft_strlen(pattern)) == 0)
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
