#include <assert.h>
#include "array_42.h"
#include "exec.h"

int get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	wait_for_children(pid_t last_pid, pid_t pgid)
{
	pid_t		pid;
	int			status;
	int			ret;

	ret = -1;
	while ((pid = waitpid(pgid, &status, 0)) != -1)
	{
		if (pid == last_pid)
			ret = get_exit_status(status);
	}
	return (ret);
}

pid_t	exec_fork(pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		error_set_context("fork: %s", strerror(errno));
		return (ERR_EXEC);
	}
	return (NO_ERROR);
}

int exec_close_fd(int fd)
{
	if (close(fd))
	{
		error_set_context("close: %s", strerror(errno));
		return (ERR_EXEC);
	}
	return (NO_ERROR);
}

int exec_dup_fd(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd))
	{
		error_set_context("dup2: %s", strerror(errno));
		return (ERR_EXEC);
	}
	return (NO_ERROR);
}

int exec_process_group_create(int pid, int pgid)
{
	if (setpgid(pid, pgid))
	{
		error_set_context("setpgid: %s", strerror(errno));
		return (ERR_EXEC);
	}
	return (NO_ERROR);
}
