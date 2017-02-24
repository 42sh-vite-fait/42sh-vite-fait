#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "errors.h"
#include "exec.h"

static int get_exit_status(int status) // TODO
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	wait_child_process_group(pid_t last_pid, pid_t pgid)
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
	if (errno != ECHILD)
	{
		error_set_context("waitpid: %s", strerror(errno));
		error_print("execution");
	}
	return (ret);
}

pid_t	exec_fork(pid_t *pid)
{
	*pid = fork();
	if (*pid < 0)
	{
		error_set_context("fork: %s", strerror(errno));
		return (ERR_EXEC);
	}
	return (NO_ERROR);
}
