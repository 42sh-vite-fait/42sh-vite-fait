#include <stdlib.h>
#include <assert.h>
#include "cbuffer_42.h"
#include "string_42.h"
#include "history.h"

extern t_history		g_history;

static const char	*get_next_line(t_string *next_line, const char *input)
{
	ssize_t	len;

	len = ft_strchrpos(input, '\n');
	if (len == 0)
		return (NULL);
	if (len > 0)
	{
		fatal_malloc(string_init_ndup(next_line, input, len));
		input += len + 1;
	}
	else
	{
		len = ft_strlen(input);
		if (len == 0)
			return (NULL);
		fatal_malloc(string_init_ndup(next_line, input, len));
		input += len;
	}
	return (input);
}

size_t		history_add(t_string *command)
{
	const char	*command_str;
	t_string	line;

	assert(command != NULL);
	command_str = command->str;
	while ((command_str = get_next_line(&line, command_str)) != NULL)
	{
		g_history.last_id += 1;
		cbuffer_push_back(&g_history.commands, &line);
	}
	return (g_history.last_id);
}
