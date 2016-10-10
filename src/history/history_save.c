#include <unistd.h>
#include <fcntl.h>
#include "typedefs_42.h"
#include "buffer_42.h"
#include "history.h"
#include "misc.h"

extern t_history	g_history;

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
int					history_save_into_file(const char *path)
{
	t_buffer	command;
	size_t		i;
	int			fd;

	if ((fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0600)) == -1)
		return (-1);

	// TODO define here
	if (ftruncate(fd, 0) == -1 || buffer_init(&command, 64) == NULL)
		return (-1);
	i = g_history.last_id;
	while (i > g_history.last_id - g_history.cbuffer.len)
	{
		if (buffer_replace(&command, history_get_id(i)) == NULL)
		{
			close(fd);
			free(command.str);
			return (-1);
		}
		if (buffer_escape(&command, '\n') == NULL)
		{
			close(fd);
			free(command.str);
			return (-1);
		}
		buffer_insert(&command, command.len, "\n", 1);
		write_all(command.str, command.len, fd);
		--i;
	}
	close(fd);
	free(command.str);
	return (0);
}
