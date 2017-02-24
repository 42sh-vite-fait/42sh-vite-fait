#include <fcntl.h>
#include <errno.h>
#include "parser.h"
#include "input.h"
#include "misc.h"
#include "errors.h"
#include "shell.h"
#include "ft_printf.h"

#define HEREDOC_PREFIX "ftsh_heredoc_"

static void	request_input(t_string *line)
{
	int	status;

	status = shell_input(line, INPUT_REQUEST_MORE); // TODO: PS2
	if (status == E_INPUT_EOF)
	{
		error_set_context("EOF unclosed");
		error_print("heredoc");
	}
	if (status != E_INPUT_OK)
		exit(1);
}

static int	fill_heredoc_file(const char *word, size_t len, int fd)
{
	t_string	line;

	fatal_malloc(string_init(&line));
	while (42)
	{
		request_input(&line);
		if (ft_strncmp(line.str, word, len) == 0 && line.str[len] == '\n')
		{
			string_shutdown(&line);
			return (NO_ERROR);
		}
		if (ft_dprintf(fd, "%s", line.str) == -1)
		{
			error_set_context("heredoc: write failed: %s", strerror(errno));
			string_shutdown(&line);
			return (ERR_HEREDOC);
		}
		string_truncate(&line, 0);
	}
}

char 		*heredoc(const char *word, size_t len)
{
	char	*filename;
	int		fd;

	if ((filename = ft_tmpfile(HEREDOC_PREFIX)) == NULL)
		return (NULL);
	if ((fd = open(filename, O_CREAT | O_WRONLY, 0600)) == -1)
		return (NULL);
	if (fill_heredoc_file(word, len, fd) != NO_ERROR)
		filename = NULL;
	if (close(fd) == -1)
		return (NULL);
	return (filename);
}
