#include <stdlib.h>
#include "history.h"
#include "cbuffer_42.h"

extern t_history	g_history;

const t_buffer		*history_get(size_t id)
{
	const t_buffer	*command_ptr;
	size_t			real_id;

	if (HIST_CONTAINS(g_history, id))
	{
		real_id = g_history.commands.len - g_history.last_id + id - 1;
		command_ptr = (const t_buffer*)cbuffer_at(&g_history.commands, real_id);
		return (command_ptr);
	}
	return (NULL);
}
