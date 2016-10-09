#include <unistd.h>
#include "typedefs_42.h"
#include "buffer_42.h"
#include "history.h"

// TODO use the lib42 one (waiting pull request acceptation)
static t_buffer		*buffer_escape_nl(t_buffer *string)
{
	char		*nl;
	size_t		nl_offset;

	nl_offset = 0;
	while ((nl = ft_strchr(string->str + nl_offset, '\n')) != NULL)
	{
		nl_offset = (size_t)(nl - string->str);
		if (buffer_insert(string, nl_offset, "\\", 1) == NULL)
			return (NULL);
		nl_offset += 2;
	}
	return (string);
}

// TODO add it in lib42 ??
static int			write_all(const char *str, size_t len, int fd)
{
	ssize_t		ret;

	ret = 0;
	while ((ret = write(fd, str + (size_t)ret, len - (size_t)ret)) > 0)
	{
		if (ret == -1)
			return (-1);
	}
	return (0);
}

// TODO does commands have '\n' at end ?
int					history_save_into_file(t_history const *history, int fd)
{
	t_buffer	command;
	size_t		i;

	//													TODO define here
	if (ftruncate(fd, 0) == -1 || buffer_init(&command, 64) == NULL)
		return (-1);
	i = history->last_id;
	while (i > history->last_id - history->cbuffer.len)
	{
		if (buffer_replace(&command, history_get_id(history, i)) == NULL)
		{
			free(command.str);
			return (-1);
		}
		if (buffer_escape_nl(&command) == NULL)
		{
			free(command.str);
			return (-1);
		}
		buffer_insert(&command, command.len, "\n", 1);
		write_all(command.str, command.len, fd);
		--i;
	}
	free(command.str);
	return (0);
}
