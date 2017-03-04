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

	ret = ERR_EXEC;
	if (redir.operator == E_TOKEN_GREAT || redir.operator == E_TOKEN_CLOBBER)
		ret = exec_redirection_output_trunc(redir.io_number, word);
	else if (redir.operator == E_TOKEN_LESS)
		ret = exec_redirection_input(redir.io_number, word);
	else if (redir.operator == E_TOKEN_DLESS
			|| redir.operator == E_TOKEN_DLESSDASH)
		ret = exec_redirection_input(redir.io_number, redir.heredoc_filename);
	else if (redir.operator == E_TOKEN_DGREAT)
		ret = exec_redirection_output_append(redir.io_number, word);
	else if (redir.operator == E_TOKEN_LESSAND)
		ret = exec_redirection_input_duplicate(redir.io_number, word);
	else if (redir.operator == E_TOKEN_GREATAND)
		ret = exec_redirection_output_duplicate(redir.io_number, word);
	else
		assert(0);
	return (ret);
}

int	exec_redirection(const t_array redirections, const t_string *input)
{
	struct s_redirection	*redir;
	char					*word;
	size_t					i;
	int						ret;

	i = 0;
	ret = NO_ERROR;
	while (i < redirections.len)
	{
		redir = array_get_at(&redirections, i);
		word = ft_strsub(input->str, redir->word->start, redir->word->len);
		ret = exec_redirection_dispatch(*redir, word);
		free(word);
		if (ret != NO_ERROR)
			break ;
		i += 1;
	}
	return (ret);
}
