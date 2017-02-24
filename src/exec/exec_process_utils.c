#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "errors.h"
#include "exec.h"

int get_exit_status(int status) // TODO
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

int exec_process_group_child_side(int pid, int pgid)
{
	if (setpgid(pid, pgid) == -1)
	{
		error_set_context("setpgid: %s", strerror(errno));
		return (ERR_EXEC);
	}
	return (NO_ERROR);
}

/*
** If the child perform the 'setpgid' and 'exec' call before the parent
** is scheduled, then the 'setpgid' call from the parent side will fail
** with errno set to 'EACCES'.
** Thus we avoid reporting an error in that case.
*/

int exec_process_group_parent_side(int pid, int pgid)
{
	if (setpgid(pid, pgid) == -1 && errno != EACCES)
	{
		error_set_context("setpgid: %s", strerror(errno));
		return (ERR_EXEC);
	}
	return (NO_ERROR);
}
