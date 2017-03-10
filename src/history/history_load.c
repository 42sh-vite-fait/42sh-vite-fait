#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "string_42.h"
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

static int			inject_commands(const t_string *file)
{
	t_string	command;
	size_t		old_off;
	size_t		off;
	char		*match;

	if (string_init(&command) == NULL)
		return (-1);
	off = 0;
	while ((match = next_real_unescaped_nl(file->str + off)) != NULL)
	{
		old_off = off;
		off = (size_t)(match - file->str);
		if (!string_init_ndup(&command, file->str + old_off, off - old_off)
			|| string_unescape_chars(&command, '\n') == NULL)
		{
			string_shutdown(&command);
			return (-1);
		}
		history_add(&command);
		off += 1;
	}
	return (0);
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
		inject_commands(&file);
	close(fd);
	string_shutdown(&file);
	return (0);
}
