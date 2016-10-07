#include <stdlib.h>
#include "history.h"
#include "cbuffer_42.h"

size_t		history_push(t_history *history, const char *command)
{
	if (history->cbuffer.len != 0)
		history->last_id += 1;
	cbuffer_push_back(&history->cbuffer, command);
	return (history->last_id);
}
