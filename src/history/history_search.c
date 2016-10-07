#include <stdlib.h>
#include "history.h"
#include "cbuffer_42.h"
#include "string_42.h"

static t_result		g_result;

t_result	*history_search_first(t_history const *hist, const char *patt)
{
	size_t		i;
	const char	*command;
	const char	*offset;

	i = hist->cbuffer.len;
	while ((command = cbuffer_get(&hist->cbuffer, i)) != NULL)
	{
		if ((offset = ft_strrstr(command, patt)) != NULL)
		{
			g_result.command_id = hist->last_id + i;
			g_result.offset = (size_t)(command - offset);
			return (&g_result);
		}
		--i;
	}
	return (NULL);
}

// t_result	*history_search_next(t_history const *hist, t_result srchres,
// 									const char *patt)
// {
// 	//
// }
