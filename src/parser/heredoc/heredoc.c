#include <fcntl.h>
#include <errno.h>
#include "parser.h"
#include "input.h"
#include "misc.h"
#include "errors.h"
#include "shell.h"
#include "ft_printf.h"
#include "expansion.h"

#define HEREDOC_PREFIX "ftsh_heredoc_"

static void	request_input(t_string *line)
{
	int	status;

	// TODO mode interactif
	status = shell_input(line, SHELL_PS2);
	if (status == CMD_EOF_)
	{
		error_set_context("EOF unclosed");
		error_print("heredoc");
	}
	if (status != OK_) // TODO exit ???
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
			return (OK_);
		}
		if (ft_dprintf(fd, "%s", line.str) == -1)
		{
			error_set_context("heredoc: write failed: %s", strerror(errno));
			string_shutdown(&line);
			return (ERROR_);
		}
		string_truncate(&line, 0);
	}
}

static char *heredoc(const char *word, size_t len)
{
	char	*filename;
	int		fd;

	if ((filename = ft_tmpfile(HEREDOC_PREFIX)) == NULL)
		return (NULL);
	if ((fd = open(filename, O_CREAT | O_WRONLY, 0600)) == -1)
		return (NULL);
	if (fill_heredoc_file(word, len, fd) != OK_)
		filename = NULL;
	if (close(fd) == -1)
		return (NULL);
	return (filename);
}

int			parser_heredoc_execute(const t_string *input, t_array *heredocs)
{
	struct s_redirection	*redir;
	char					*here_end;
	size_t					i;

	i = 0;
	while (i < heredocs->len)
	{
		redir = *(struct s_redirection**)array_get_at(heredocs, i);
		here_end = expand_quote_removal(input->str + redir->word->start, redir->word->len);
		redir->heredoc_filename = heredoc(here_end, ft_strlen(here_end));
		free(here_end);
		if (redir->heredoc_filename == NULL)
			return (ERROR_);
		i += 1;
	}
	return (OK_);
}

void		parser_heredoc_push(t_parser *parser, const struct s_redirection *redir)
{
	fatal_malloc(array_push(&parser->heredocs, &redir));
}
