#include <stdlib.h>
#include "history.h"
#include "cbuffer_42.h"

char const		*history_get_id(t_history const *history, size_t id)
{
	if (history_contains(history, id))
		return (CBUFFER_GET(&history->cbuffer, id - history->last_id));
	return (NULL);
}
