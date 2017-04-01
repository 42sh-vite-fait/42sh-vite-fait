/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:37:04 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:37:21 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include "parser.h"
#include "input.h"
#include "misc.h"
#include "errors.h"
#include "shell.h"
#include "ft_printf.h"
#include "expansion.h"
#include "exec.h"

#define HEREDOC_PREFIX "ftsh_heredoc_"

static void	heredoc_print_eof_error(t_array *heredocs)
{
	parser_heredoc_shutdown(heredocs);
	error_set_context("EOF unclosed");
	error_print("heredoc");
	exit(1);
}

static int	fill_heredoc_file(const char *word, size_t len, int fd)
{
	t_string	line;
	int			status;

	fatal_malloc(string_init(&line));
	while (42)
	{
		status = shell_input(&line, SHELL_PS2);
		if (status != OK_)
			return (status);
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

static int	heredoc(const char *word, size_t len, char **filename)
{
	int		fd;
	int		status;

	if ((*filename = ft_tmpfile(HEREDOC_PREFIX)) == NULL)
		return (ERROR_);
	if ((fd = open(*filename, O_CREAT | O_WRONLY, 0600)) == -1)
	{
		error_set_context("heredoc: %s", strerror(errno));
		free(*filename);
		return (ERROR_);
	}
	status = fill_heredoc_file(word, len, fd);
	if (exec_close_fd(fd) == -1)
		return (ERROR_);
	return (status);
}

int			parser_heredoc_execute(const t_string *input, t_array *heredocs)
{
	struct s_redirection	*redir;
	char					*here_end;
	size_t					i;
	int						ret;

	i = 0;
	while (i < heredocs->len)
	{
		redir = *(struct s_redirection**)array_get_at(heredocs, i);
		here_end = expand_quote_removal(input->str + redir->word->start,
				redir->word->len);
		ret = heredoc(here_end, ft_strlen(here_end), &redir->heredoc_filename);
		free(here_end);
		if (ret == CMD_EOF_)
			heredoc_print_eof_error(heredocs);
		else if (ret != OK_)
			return (ret);
		i += 1;
	}
	return (OK_);
}

void		parser_heredoc_push(t_parser *parser,
		const struct s_redirection *redir)
{
	fatal_malloc(array_push(&parser->heredocs, &redir));
}
