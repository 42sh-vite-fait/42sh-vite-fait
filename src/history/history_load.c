#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "string_42.h"
#include "history.h"
#include "misc.h"

#define HIST_MAX_SIZE 0x1000000

extern t_history	g_history;

static void			inject_commands(const char *file)
{
	t_string	command;

	while ((file = str_token(&command, file, '\n')) != NULL)
		history_add(&command);
}

int					history_load_from_file(const char *path)
{
	t_string	file;
	int			fd;
	struct stat	stat;

	if ((fd = open(path, O_RDONLY | O_CLOEXEC)) == -1)
		return (-1);
	fatal_malloc(string_init(&file));
	if (fstat(fd, &stat) == 0 &&
		S_ISREG(stat.st_mode) &&
		stat.st_size <= HIST_MAX_SIZE &&
		string_read_from_fd(&file, fd) != NULL)
		inject_commands(file.str);
	close(fd);
	string_shutdown(&file);
	return (0);
}
