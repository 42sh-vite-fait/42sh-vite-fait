#include "redirections.h"
#include "array_42.h"
#include "ast.h"

/*
** Source: http://stackoverflow.com/a/12340767
*/

static bool	is_fd_open(int fd)
{
	errno = 0;
	return (fcntl(fd, F_GETFD) != -1 || errno != EBADF)
}

static int	restore_standard_fd(int fd)
{
	if (dup2(fd, get_backup_standard_fd(fd)) == -1)
		return (ERR_FCNTL);
	return (NO_ERROR);
}

static int	close_opened_file(int fd)
{
	if (is_fd_open(fd) && close(fd) == -1)
		return (ERR_CLOSE);
	return (NO_ERROR);
}

int	undo_redirection(t_array redirections)
{
	struct s_redirection	redir;
	size_t					i;

	i = redirections.len;
	while (i > 0)
	{
		i -= 1;
		redir = *(struct s_redirection*)array_get_at(&redirections, i);
		if (IS_FD_STANDARD(redir.io_number))
			ret = restore_standard_fd(redir.io_number);
		else
			ret = close_opened_file(redir.io_number);
		if (ret != NO_ERROR)
			ft_perrorn(NULL, ret);
	}
	return (ret);
}
