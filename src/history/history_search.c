#include <stdlib.h>
#include <stdbool.h>
#include "history.h"
#include "cbuffer_42.h"
#include "string_42.h"

bool	history_search(t_history const *hist, const char *patt, t_result *ret)
{
	size_t		i;
	const char	*command;
	const char	*offset;

	i = hist->cbuffer.len;
	while ((command = cbuffer_get(&hist->cbuffer, i)) != NULL)
	{
		if ((offset = ft_strrstr(command, patt)) != NULL)
		{
			if (ret != NULL)
			{
				ret->command_id = hist->last_id + i;
				ret->offset = (size_t)(command - offset);
			}
			return (true);
		}
		--i;
	}
	return (false);
}

// bool		history_search_next(t_history const *history, const char *patt,
// 								t_result const *from, t_result *ret)
// {
// 	//
// }
