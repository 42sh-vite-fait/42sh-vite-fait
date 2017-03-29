#include <stdlib.h>
#include <assert.h>
#include "array_42.h"
#include "exec.h"
#include "ast.h"

/*
** 2.7 Redirection
** A failure to open or create a file shall cause a redirection to fail.
** And the command shall also fail
*/

static int	exec_redirection_dispatch(struct s_redirection redir,
		const char *word)
{
	int		ret;

	ret = ERROR_;
	if (redir.operator == E_TOKEN_GREAT)
		ret = exec_redirection_output_trunc(redir.io_number, word);
	else if (redir.operator == E_TOKEN_LESS)
		ret = exec_redirection_input(redir.io_number, word);
	else if (redir.operator == E_TOKEN_DLESS)
		ret = exec_redirection_input(redir.io_number, redir.heredoc_filename);
	else if (redir.operator == E_TOKEN_DGREAT)
		ret = exec_redirection_output_append(redir.io_number, word);
	else if (redir.operator == E_TOKEN_LESSAND)
		ret = exec_redirection_input_duplicate(redir.io_number, word);
	else if (redir.operator == E_TOKEN_GREATAND)
		ret = exec_redirection_output_duplicate(redir.io_number, word);
	else if (redir.operator == E_TOKEN_LESSGREAT)
		ret = exec_redirection_output_input(redir.io_number, word);
	else
		error_set_context("redirection operator unknown");
	return (ret);
}

/*
** Source: http://stackoverflow.com/a/12340767
*/

bool	is_fd_open(int fd)
{
	errno = 0;

	return (fcntl(fd, F_GETFD) != -1 || errno != EBADF);
}

int	exec_redirection(t_array redirections, const t_string *input)
{
	struct s_redirection	*redir;
	char					*word;
	size_t					i;
	int						ret;

	i = 0;
	ret = OK_;
	while (i < redirections.len)
	{
		redir = array_get_at(&redirections, i);
		word = fatal_malloc(ft_strsub(input->str, redir->word->start,
					redir->word->len));
		ret = exec_redirection_dispatch(*redir, word);
		free(word);
		if (ret != OK_)
			break ;
		i += 1;
	}
	return (ret);
}
