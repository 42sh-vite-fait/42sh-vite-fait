/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_undo.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:01:48 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:12:56 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "exec.h"
#include "array_42.h"
#include "ast.h"

static int	close_opened_file(int io_number)
{
	if (is_fd_open(io_number))
		return (exec_close_fd(io_number));
	return (OK_);
}

static int	restore_standard_fd(int io_number)
{
	int	fd_backup;

	fd_backup = io_number + E_FD_BACKUP_OFFSET;
	if (is_fd_open(fd_backup))
		return (exec_dup_fd(fd_backup, io_number));
	else
		return (close_opened_file(io_number));
}

int			undo_redirection(const t_array redirections)
{
	struct s_redirection	redir;
	size_t					i;
	int						ret;

	i = redirections.len;
	ret = OK_;
	while (i > 0)
	{
		i -= 1;
		redir = *(struct s_redirection*)array_get_at(&redirections, i);
		if (IS_FD_STANDARD(redir.io_number))
			ret = restore_standard_fd(redir.io_number);
		else
			ret = close_opened_file(redir.io_number);
		if (ret != OK_)
			break ;
	}
	return (ret);
}
