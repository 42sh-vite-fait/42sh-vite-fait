#include <unistd.h>
#include <stdlib.h>
#include "array_42.h"
#include "parser.h"

void	parser_heredoc_shutdown(t_array *heredocs)
{
	struct s_redirection	*redir;

	while (heredocs->len)
	{
		array_pop(heredocs, &redir);
		unlink(redir->heredoc_filename);
		free(redir->heredoc_filename);
	}
}
