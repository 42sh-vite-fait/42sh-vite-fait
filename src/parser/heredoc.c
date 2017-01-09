#include <fcntl.h>
#include "parser.h"
#include "input.h"
#include "misc.h"
#include "errors.h"
#include "ft_printf.h"

#define HEREDOC_PREFIX "ftsh_heredoc_"

static int	fill_heredoc_file(const t_token *word, int fd)
{
	char	*line;

	while (42)
	{
		if (ft_printf("> ") == -1) // TODO: PS2
		{
			error_set_context("heredoc: write failed: %s", strerror(errno));
			return (ERR_HEREDOC);
		}
		line = input_readline();
		if (ft_strncmp(line, word->str, word->len) == 0
				&& line[word->len] == '\n')
			return (NO_ERROR);
		if (ft_dprintf(fd, "%s", line) == -1)
		{
			error_set_context("heredoc: write failed: %s", strerror(errno));
			return (ERR_HEREDOC);
		}
	}
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
