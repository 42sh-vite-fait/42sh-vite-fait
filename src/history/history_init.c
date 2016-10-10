#include <stdlib.h>
#include "typedefs_42.h"
#include "cbuffer_42.h"
#include "history.h"

extern t_history	g_history;
t_history			g_history;

static void		del_string(void *string)
{
	free(*(char**)string);
}

int				history_init(size_t limit)
{
	if (!cbuffer_init(&g_history.cbuffer, limit, sizeof(char*), del_string))
		return (-1);
	g_history.last_id = 0;
	return (0);
}

