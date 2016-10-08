#include <stdlib.h>
#include "typedefs_42.h"
#include "cbuffer_42.h"
#include "history.h"

static void		delete_string(void *string)
{
	free(*(char**)string);
}

t_history		*history_new(size_t limit)
{
	t_history	*history;

	if ((history = malloc(sizeof(t_history))) == NULL)
		return (NULL);
	if (history_init(history, limit) == NULL)
	{
		free(history);
		return (NULL);
	}
	return (history);
}

t_history		*history_init(t_history *hist, size_t len)
{
	if (cbuffer_init(&hist->cbuffer, len, sizeof(char*), delete_string) == NULL)
		return (NULL);
	hist->last_id = 0;
	return (hist);
}

