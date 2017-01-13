#include <stdlib.h>
#include "array_42.h"
#include "redirections.h"
#include "ast.h"

static int	exec_redirection_dispatch(struct s_redirection redir)
{
	const char	*word;
	int			ret;

	word = ft_strsub(redir.token->str, 0, redir.token->len);
	if (redir.operator == GREAT || redir.operator == CLOBBER)
		ret = exec_redirection_output_trunc(redir.io_number, word);
	else if (redir.operator == LESS)
		ret = exec_redirection_input(redir.io_number, word);
	else if (redir.operator == DLESS || redir.operator == DLESSDASH)
		ret = exec_redirection_input(redir.io_number, redir.heredoc_filename);
	else if (redir.operator == DGREAT)
		ret = exec_redirection_output_append(redir.io_number, word);
	else if (redir.operator == LESSAND)
		ret = exec_redirection_input_duplicate(redir.io_number, word);
	else if (redir.operator == GREATAND)
		ret = exec_redirection_output_duplicate(redir.io_number, word);
	else
		ret = -1; // TODO
	free(word);
	return (ret);
}

int	exec_redirection(t_array redirections)
{
	struct s_redirection	redir;
	size_t					i;

	i = 0;
	while (i < redirections.len)
	{
		redir = *(struct s_redirection*)array_get_at(&redirections, i);
		ret = exec_redirection_dispatch(redir);
		if (ret != NO_ERROR)
			break ;
		i += 1;
	}
	return (ret);
}
