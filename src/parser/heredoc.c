#include <fcntl.h>
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

	status = shell_input(line, SHELL_PS2); // TODO: PS2
	if (status == E_INPUT_EOF)
	{
		error_set_context("EOF unclosed");
		error_print("heredoc");
	}
	if (status != E_INPUT_OK)
		exit(1);
}

static int	fill_heredoc_file(const t_token *word, int fd)
{
	t_string	line;

	while (42)
	{
		request_input(&line);
		if (ft_strncmp(line.str, word->str, word->len) == 0
				&& line.str[word->len] == '\n')
			return (NO_ERROR);
		if (ft_dprintf(fd, "%s", line) == -1)
		{
			error_set_context("heredoc: write failed: %s", strerror(errno));
			return (ERR_HEREDOC);
		}
	}
	// TODO: Supprimer l'input
	// TODO: Quoi faire si input_get_line() retourne NULL
}

char 		*heredoc(const t_token *word)
{
	char	*filename;
	int		fd;

	if ((filename = ft_tmpfile(HEREDOC_PREFIX)) == NULL)
		return (NULL);
	if ((fd = open(filename, O_CREAT | O_WRONLY, 0600)) == -1)
		return (NULL);
	if (fill_heredoc_file(word, fd) != NO_ERROR)
		filename = NULL;
	if (close(fd) == -1)
		return (NULL);
	return (filename);
}
