#include "exec.h"
#include "array_42.h"
#include "ast.h"

/*
** Source: http://stackoverflow.com/a/12340767
*/

static bool	is_fd_open(int fd)
{
	errno = 0;

	return (fcntl(fd, F_GETFD) != -1 || errno != EBADF);
}

static int	restore_standard_fd(int io_number)
{
	return (exec_dup_fd(exec_backup_get_standard_fd(io_number), io_number));
}

static int	close_opened_file(int io_number)
{
	if (is_fd_open(io_number))
		return (exec_close_fd(io_number));
	return (NO_ERROR);
}

int	undo_redirection(const t_array redirections)
{
	struct s_redirection	redir;
	size_t					i;
	int						ret;

	i = redirections.len;
	ret = NO_ERROR;
	while (i > 0)
	{
		i -= 1;
		redir = *(struct s_redirection*)array_get_at(&redirections, i);
		if (IS_FD_STANDARD(redir.io_number))
			ret = restore_standard_fd(redir.io_number);
		else
			ret = close_opened_file(redir.io_number);
		if (ret != NO_ERROR)
			break ;
	}
	return (ret);
}
