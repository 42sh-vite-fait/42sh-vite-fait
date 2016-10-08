#include <stdlib.h>
#include "history.h"
#include "cbuffer_42.h"

char const		*history_get_id(t_history const *hist, size_t id)
{
	size_t		real_id;
	const char	**command_ptr;

	if (history_contains(hist, id))
	{
		real_id = hist->cbuffer.len - hist->last_id + id - 1;
		command_ptr = (const char**)cbuffer_get(&hist->cbuffer, real_id);
		return (*command_ptr);
	}
	return (NULL);
}
