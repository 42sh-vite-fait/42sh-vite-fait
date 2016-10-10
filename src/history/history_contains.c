#include <stdbool.h>
#include <stdlib.h>
#include "history.h"

extern t_history	g_history;

bool	history_contains(size_t id)
{
	return (id <= g_history.last_id
			&& id > g_history.last_id - g_history.cbuffer.len);
}
