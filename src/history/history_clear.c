#include <stdlib.h>
#include "typedefs_42.h"
#include "cbuffer_42.h"
#include "history.h"

extern t_history	g_history;

void			history_clear(void)
{
	cbuffer_truncate_from_back(&g_history.commands, 0);
	g_history.last_id = 0;
}
