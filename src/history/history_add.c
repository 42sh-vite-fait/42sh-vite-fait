#include <stdlib.h>
#include <assert.h>
#include "cbuffer_42.h"
#include "string_42.h"
#include "history.h"
#include "misc.h"

extern t_history		g_history;

size_t		history_add(t_string *command)
{
	t_string	line;

	assert(command != NULL);
	fatal_malloc(string_clone(&line, command));
	if (line.len && line.str[line.len - 1] == '\n')
		string_truncate(&line, line.len - 1);
	cbuffer_push_back(&g_history.commands, &line);
	g_history.last_id += 1;
	return (g_history.last_id);
}
