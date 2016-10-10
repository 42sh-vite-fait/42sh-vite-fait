#include <stdlib.h>
#include "history.h"
#include "cbuffer_42.h"

extern t_history		g_history;

size_t		history_push(const char *command)
{
	g_history.last_id += 1;
	cbuffer_push_back(&g_history.cbuffer, &command);
	return (g_history.last_id);
}
