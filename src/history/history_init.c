#include <stdlib.h>
#include "typedefs_42.h"
#include "cbuffer_42.h"
#include "history.h"
#include "error_42.h"

extern t_history	g_history;
t_history			g_history;

int				history_init(size_t limit)
{
	fatal_malloc(cbuffer_init(&g_history.commands, limit, sizeof(t_string),
								(void (*)(void *))string_shutdown));
	g_history.last_id = 0;
	return (0);
}

void			history_shutdown(void)
{
	cbuffer_shutdown(&g_history.commands);
}
