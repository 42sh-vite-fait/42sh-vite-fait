#include <unistd.h>
#include <string.h>
#include "errors.h"
#include "exec.h"

int exec_close_fd(int fd)
{
	if (close(fd) == -1)
	{
		error_set_context("close: %s", strerror(errno));
		return (ERR_EXEC);
	}
	return (NO_ERROR);
}

int exec_dup_fd(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		error_set_context("dup2: %s", strerror(errno));
		return (ERR_EXEC);
	}
	return (NO_ERROR);
}
