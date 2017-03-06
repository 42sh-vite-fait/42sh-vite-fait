#include <unistd.h>
#include <fcntl.h>
#include "typedefs_42.h"
#include "string_42.h"
#include "memory.h"
#include "history.h"
#include "misc.h"

extern t_history	g_history;

static int			inject_commands(const char *file)
{
	t_string	command;

	while ((file = str_token(&command, file, '\n')) != NULL)
		history_add(&command);
	return (0);
}

int					history_load_from_file(const char *path)
{
	t_string	file;
	int			fd;

	if ((fd = open(path, O_RDONLY | O_CLOEXEC)) == -1)
		return (-1);
	if (string_read_from_fd(&file, fd) == NULL)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	if (inject_commands(file.str) == -1)
	{
		string_shutdown(&file);
		return (-1);
	}
	string_shutdown(&file);
	return (0);
}
