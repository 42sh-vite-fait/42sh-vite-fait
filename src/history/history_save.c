#include <unistd.h>
#include <fcntl.h>
#include "typedefs_42.h"
#include "string_42.h"
#include "history.h"
#include "misc.h"

extern t_history	g_history;

static int	convert_and_write_to_file(t_string *command, size_t cmd_id, int fd)
{
	fatal_malloc(string_replace(command, history_get(cmd_id)->str));
	string_escape_chars(command, '\n');
	fatal_malloc(string_insert(command, command->len, "\n", 1));
	if (string_write_to_fd(command, fd) == -1)
		return (-1);
	return (0);
}

int			history_save_into_file(const char *path)
{
	t_string	command;
	size_t		i;
	int			fd;

	if ((fd = open(path, O_CREAT | O_WRONLY | O_TRUNC | O_CLOEXEC, 0600)) == -1)
		return (-1);
	fatal_malloc(string_init(&command));
	i = g_history.last_id - g_history.commands.len + 1;
	while (i <= g_history.last_id)
	{
		if (convert_and_write_to_file(&command, i, fd) == -1)
			break ;
		i++;
	}
	close(fd);
	string_shutdown(&command);
	return (0);
}
