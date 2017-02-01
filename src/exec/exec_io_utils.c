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

/*
** 'origin' ---> a ; 'dup' ---> b
** dup2(oldfd, newfd)
** 'origin' ---> a ; 'dup' ---> a
*/

int exec_dup_fd(int origin, int dup)
{
	if (dup2(origin, dup) == -1)
	{
		error_set_context("dup2: %s", strerror(errno));
		return (ERR_EXEC);
	}
	return (NO_ERROR);
}
