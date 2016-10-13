#include <stdio.h> // delete

#include <unistd.h>
#include <fcntl.h>
#include "typedefs_42.h"
#include "buffer_42.h"
#include "memory.h"
#include "history.h"
#include "misc.h"

extern t_history	g_history;

static char			*next_real_unescaped_nl(const char *string)
{
	char		*match;
	size_t		off;

	off = 0;
	while ((match = ft_strchr(string + off, '\n')) != NULL)
	{
		if (match == string || !is_escaped(match, string + off))
			return (match);
		off = (size_t)(match - string) + 1;
	}
	return (NULL);
}

static t_buffer		*read_whole_file(t_buffer *file, const char *path)
{
	int		fd;

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		free(file->str);
		return (NULL);
	}
	if (buffer_read_from_fd(file, fd) == NULL)
	{
		close(fd);
		free(file->str);
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
		if (buffer_nreplace(cmd, file->str + old_off, off - old_off) == NULL)
			return (-1);
		if (buffer_unescape_chars(cmd, '\n') == NULL)
			return (-1);
		history_add(*cmd);
		off += 1;
	}
	if (buffer_replace(cmd, file->str + off) == NULL)
		return (-1);
	if (buffer_unescape_chars(cmd, '\n') == NULL)
		return (-1);
	history_add(*cmd);
	return (0);
}

int					history_load_from_file(const char *path)
{
	t_buffer	tmp_cmd;
	t_buffer	file;

	if (buffer_init(&file, MEM_PAGE_SIZE) == NULL)
		return (-1);
	if (read_whole_file(&file, path) == NULL)
	{
		free(file.str);
		return (-1);
	}
	if (buffer_init(&tmp_cmd, BUFFER_INIT_SIZE) == NULL)
	{
		free(file.str);
		return (-1);
	}
	if (inject_commands(&file, &tmp_cmd) == -1)
	{
		free(file.str);
		free(tmp_cmd.str);
		return (-1);
	}
	free(file.str);
	return (0);
}
