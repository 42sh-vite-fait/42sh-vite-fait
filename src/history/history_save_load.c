#include <stdio.h> // delete

#include <unistd.h>
// #include <fcntl.h>
#include "typedefs_42.h"
#include "buffer_42.h"
#include "history.h"
#include "error_42.h"

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
		{
			// ft_perror
			return (NULL);
		}
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
		{
			// ft_perror
			return (-1);
		}
	}
	return (0);
}

// TODO does commands have '\n' at end ?
int					history_save_into_file(t_history const *history, int fd)
{
	const char	*command_str;
	t_buffer	*command;
	size_t		i;

	if (ftruncate(fd, 0) == -1)
		return (-1); // TODO errno ?

	// TODO use buffer[PAGE_SIZE] for perfs ???

	command = NULL;
	i = history->last_id;
	while (i > history->last_id - history->cbuffer.len)
	{
		command_str = history_get_id(history, i);
		if ((command == NULL && (command = buffer_dup(command_str)) == NULL) ||
			(command = buffer_replace(command, command_str)) == NULL)
		{
			// ft_perror("malloc: Out of memory");
			return (-1);
		}
		if (buffer_escape_nl(command) == NULL)
		{
			// ft_perror
			return (-1);
		}
		buffer_insert(command, command->len, "\n", 1);
		write_all(command->str, command->len, fd);
		--i;
	}
	return (0);
}

// TODO add it to buffer in lib42 ?? (more generic)
static t_buffer		*buffer_unescape_nl(t_buffer *string)
{
	char		*escaped_nl;
	size_t		offset;

	offset = 0;
	while ((escaped_nl = ft_strstr(string->str + offset, "\\\n")) != NULL)
	{
		offset = (size_t)(escaped_nl - string->str);
		if (buffer_remove(string, offset, 1) == 0)
		{
			// ft_perror
			return (NULL);
		}
	}
	return (string);
}

static int			read_all(t_buffer *buffer, int fd)
{
	(void)buffer;
	(void)fd;
	return (0);
}

int					history_load_from_file(t_history *history, int fd)
{
	const char	*command_str;
	t_buffer	whole_file;
	t_buffer	*buffer;

	if (read_all(&whole_file, fd) == -1)
	{
		// ft_perror
		return (-1);
	}
	buffer = NULL;
	while (whole_file.len != 0)
	{
		command_str = NULL;
		if ((buffer == NULL && (buffer = buffer_dup(command_str)) == NULL) ||
			(buffer = buffer_replace(buffer, command_str)) == NULL)
		{
			// ft_perror
			return (-1);
		}
		if (buffer->len != 0)
		{
			buffer_unescape_nl(buffer);
			history_push(history, buffer->str);
		}
		//
	}

	//
	return (0);
}
