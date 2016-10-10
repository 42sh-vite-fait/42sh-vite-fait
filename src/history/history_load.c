#include <stdio.h> // delete

#include <unistd.h>
#include <fcntl.h>
#include "typedefs_42.h"
#include "buffer_42.h"
#include "history.h"
#include "misc.h"

extern t_history	g_history;

static char			*next_real_unescaped_nl(const char *file)
{
	char		*match;
	size_t		off;

	off = 0;
	while ((match = ft_strchr(file + off, '\n')) != NULL)
	{
		if (match == file || !(rev_count_dup(match - 1, file + off, '\\') & 1))
			return (match);
		off = (size_t)(match - file) + 1;
	}
	return (NULL);
}

static int			push_unescaped(t_buffer *buffer)
{
	if (buffer->len != 0)
	{
		if (buffer_unescape_chars(buffer, '\n') == NULL)
			return (-1);
		history_push(ft_strdup(buffer->str));
	}
	return (0);
}

static t_buffer		*read_whole_file(const char *path)
{
	t_buffer	*file;
	int			fd;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (NULL);
	if ((file = buffer_read_from_fd(fd)) == NULL)
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	return (file);
}

static int			inject_commands(const t_buffer *file, t_buffer *cmd)
{
	char		*match;
	size_t		old_off;
	size_t		off;

	off = 0;
	while ((match = next_real_unescaped_nl(file->str + off)) != NULL)
	{
		old_off = off;
		off = (size_t)(match - file->str);
		buffer_remove(cmd, cmd->len - 1, 1);
		if (buffer_nreplace(cmd, file->str + old_off, off - old_off) == NULL
			|| push_unescaped(cmd) == -1)
		{
			return (-1);
		}
		off += 1;
	}
	if (!buffer_replace(cmd, file->str + off) || push_unescaped(cmd) == -1)
	{
		return (-1);
	}
	return (0);
}

// TODO waiting all pull requests to be accepted to clean up this
int				history_load_from_file(const char *path)
{
	t_buffer	command;
	t_buffer	*file;

	if ((file = read_whole_file(path)) == NULL)
		return (-1);
	if (buffer_init(&command, CMD_LEN) == NULL)
	{
		buffer_destroy(file);
		return (-1);
	}
	if (inject_commands(file, &command) == -1)
	{
		buffer_destroy(file);
		free(command.str);
		return (-1);
	}
	buffer_destroy(file);
	free(command.str);
	return (0);
}
