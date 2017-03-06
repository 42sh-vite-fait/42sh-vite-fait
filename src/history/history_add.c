#include <stdlib.h>
#include <assert.h>
#include "cbuffer_42.h"
#include "string_42.h"
#include "history.h"
#include "misc.h"

extern t_history		g_history;

size_t		history_add(t_string *command)
{
	const char	*command_str;
	t_string	line;

	assert(command != NULL);
	command_str = command->str;
	while ((command_str = str_token(&line, command_str, '\n')) != NULL)
	{
		g_history.last_id += 1;
		cbuffer_push_back(&g_history.commands, &line);
	}
	return (g_history.last_id);
}
