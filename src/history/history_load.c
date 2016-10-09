#include <unistd.h>
#include "typedefs_42.h"
#include "buffer_42.h"
#include "history.h"

// TODO use the lib42 one (waiting pull request acceptation)
static t_buffer		*buffer_unescape_nl(t_buffer *string)
{
	char		*escaped_nl;
	size_t		offset;

	offset = 0;
	while ((escaped_nl = ft_strstr(string->str + offset, "\\\n")) != NULL)
	{
		offset = (size_t)(escaped_nl - string->str);
		if (buffer_remove(string, offset, 1) == 0)
			return (NULL);
	}
	return (string);
}

#define BUFF_SIZE (4096) // TODO pagesize + in .h file

static char			*buffer_read_all(int fd)
{
	char		read_buff[BUFF_SIZE];
	t_buffer	buffer;
	ssize_t		ret;

	buffer_init(&buffer, BUFF_SIZE);
	while ((ret = read(fd, read_buff, BUFF_SIZE)) == BUFF_SIZE)
	{
		if (buffer_insert(&buffer, buffer.len, read_buff, (size_t)ret) == NULL)
		{
			free(buffer.str);
			return (NULL);
		}
	}
	if (buffer_insert(&buffer, buffer.len, read_buff, (size_t)ret) == NULL)
	{
		free(buffer.str);
		return (NULL);
	}
	return (buffer.str);
}

static char			*next_real_unescaped_nl(const char *file)
{
	char		*match;
	size_t		off;

	off = 0;
	while ((match = ft_strchr(file + off, '\n')) != NULL)
	{
		if (match == file || (match != file && *(match - 1) != '\\'))
			return (match);
		off = (size_t)(match - file) + 1;
	}
	return (NULL);
}

static int			history_push_unescaped(t_buffer *buffer, t_history *history)
{
	if (buffer->len != 0)
	{
		if (buffer_unescape_nl(buffer) == NULL)
			return (-1);
		history_push(history, ft_strdup(buffer->str));
	}
	return (0);
}

// TODO waiting all pull requests to be accepted to clean up this
int					history_load_from_file(t_history *history, int fd)
{
	char		*file;
	size_t		old_off;
	size_t		off;
	t_buffer	buffer;
	char		*match;

	// TODO read file step by step
	if ((file = buffer_read_all(fd)) == NULL)
		return (-1);

	// TODO pagesize
	if (buffer_init(&buffer, BUFF_SIZE) == NULL)
	{
		free(file);
		return (-2); // TODO error defines
	}

	off = 0;
	while ((match = next_real_unescaped_nl(file + off)) != NULL)
	{
		old_off = off;
		off = (size_t)(match - file);
		buffer_remove(&buffer, buffer.len - 1, 1);
		if (buffer_nreplace(&buffer, file + old_off, off - old_off) == NULL ||
			history_push_unescaped(&buffer, history) == -1)
		{
			free(file);
			free(buffer.str);
			return (-3);
		}
		off += 1;
	}

	if (buffer_replace(&buffer, file + off) == NULL ||
		history_push_unescaped(&buffer, history) == -1)
	{
		free(file);
		free(buffer.str);
		return (-3);
	}

	free(file);
	free(buffer.str);
	return (0);
}
