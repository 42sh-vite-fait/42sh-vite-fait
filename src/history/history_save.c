#include <stdio.h> // delete

#include <unistd.h>
// #include <fcntl.h>
#include "typedefs_42.h"
#include "buffer_42.h"
#include "history.h"

// TODO add it to buffer in lib42 ?? (more generic)
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

// TODO add it in lib42 ?? (more generic)
static int			write_all(const char *str, size_t len, int fd)
{
	ssize_t		ret;

	ret = 0;
	while ((ret = write(fd, str + (size_t)ret, len - (size_t)ret)) != 0)
	{
		if (ret == -1)
			return (-1);
	}
	return (0);
}

// TODO does commands have '\n' at end ?
int					history_save_into_file(t_history const *history, int fd)
{
	const char	*command_str;
	t_buffer	*command; // TODO remove star*
	size_t		i;

	if (ftruncate(fd, 0) == -1)
		return (-1); // TODO errno ?

	// TODO use buffer[PAGE_SIZE] for perfs ???

	command = NULL;
	i = history->last_id;
	while (i > history->last_id - history->cbuffer.len)
	{
		command_str = history_get_id(history, i);
		// TODO allways buffer_replace
		if ((command == NULL && (command = buffer_dup(command_str)) == NULL) ||
			(command = buffer_replace(command, command_str)) == NULL)
		{
			if (command)
				buffer_destroy(command);
			return (-1);
		}
		if (buffer_escape_nl(command) == NULL)
		{
			buffer_destroy(command);
			return (-1);
		}
		buffer_insert(command, command->len, "\n", 1);
		write_all(command->str, command->len, fd);
		--i;
	}
	buffer_destroy(command);
	return (0);
}
