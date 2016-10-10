#include <stdlib.h>
#include "history.h"
#include "cbuffer_42.h"

extern t_history	g_history;

char const		*history_get_id(size_t id)
{
	size_t		real_id;
	const char	**command_ptr;

	if (history_contains(id))
	{
		real_id = g_history.cbuffer.len - g_history.last_id + id - 1;
		command_ptr = (const char**)cbuffer_get(&g_history.cbuffer, real_id);
		return (*command_ptr);
	}
	return (NULL);
}
