#include <unistd.h>
#include <fcntl.h>
#include "typedefs_42.h"
#include "buffer_42.h"
#include "history.h"
#include "misc.h"

extern t_history	g_history;

static int	convert_and_write_to_file(t_buffer *command, size_t cmd_id, int fd)
{
	if (buffer_replace(command, history_get(cmd_id)->str) == NULL)
		return (-1);
	if (buffer_escape_chars(command, '\n') == NULL)
		return (-1);
	if (buffer_insert(command, command->len, "\n", 1) == NULL)
		return (-1);
	if (buffer_write_to_fd(command, fd) == -1)
		return (-1);
	return (0);
}

int			history_save_into_file(const char *path)
{
	t_buffer	command;
	size_t		i;
	int			fd;

	if ((fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0600)) == -1)
		return (-1);

	if (ftruncate(fd, 0) == -1 || !buffer_init(&command, BUFFER_INIT_SIZE))
		return (-1);
	i = g_history.last_id;
	while (i > g_history.last_id - g_history.commands.len)
	{
		if (convert_and_write_to_file(&command, i, fd) == -1)
		{
			close(fd);
			free(command.str);
			return (-1);
		}
		--i;
	}
	close(fd);
	free(command.str);
	return (0);
}
