#include <assert.h>
#include "exec.h"
#include "array_42.h"
#include "ast.h"

#include <stdio.h>
static int	restore_standard_fd(int io_number)
{
	int	fd_copy;

	fd_copy = exec_get_backup_fd(io_number);
	printf("### DEBUG %s\n", __func__);
	assert(fd_copy == FD_CLOSED);
	if (fd_copy != FD_CLOSED)
		return (exec_dup_fd(fd_copy, io_number));
	return (OK_);
}

static int	close_opened_file(int io_number)
{
	if (is_fd_open(io_number))
		return (exec_close_fd(io_number));
	return (OK_);
}

int	undo_redirection(const t_array redirections)
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
