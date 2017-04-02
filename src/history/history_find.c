#include <stdlib.h>
#include <stdbool.h>
#include "history.h"
#include "cbuffer_42.h"
#include "string_42.h"

extern t_history	g_history;

size_t		history_find_start_with(const char *pattern)
{
	const t_string	*cmd;
	size_t			i;

	i = g_history.commands.len;
	while (i > 0)
	{
		cmd = cbuffer_get_at(&g_history.commands, i - 1);
		if (ft_strncmp(cmd->str, pattern, ft_strlen(pattern)) == 0)
			return (g_history.last_id - g_history.commands.len + i);
		--i;
	}
	return (0);
}
