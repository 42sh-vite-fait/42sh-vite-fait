#include <stdlib.h>
#include "cbuffer_42.h"
#include "string_42.h"
#include "history.h"

extern t_history		g_history;

size_t		history_add(t_string *command)
{
	if (command->len > 0 && command->str[command->len - 1] == '\n')
	{
		if (string_truncate(command, command->len - 1) == NULL)
			return (0);
	}
	g_history.last_id += 1;
	cbuffer_push_back(&g_history.commands, command);
	return (g_history.last_id);
}
