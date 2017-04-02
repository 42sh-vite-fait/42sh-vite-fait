/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_shutdown.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:37:04 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:37:06 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (redir->heredoc_filename == NULL)
			continue ;
		unlink(redir->heredoc_filename);
		free(redir->heredoc_filename);
	}
}
