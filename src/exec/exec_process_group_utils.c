#include <signal.h>
#include <stdlib.h>
#include "exec.h"
#include "errors.h"
#include "sig.h"

static int exec_set_process_group_child_side(int pid, int pgid)
{
	if (setpgid(pid, pgid) == -1)
	{
		error_set_context("child: setpgid: %s", strerror(errno));
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

static int exec_set_process_group_parent_side(int pid, int pgid)
{
	if (setpgid(pid, pgid) == -1 && errno != EACCES)
	{
		error_set_context("parent: setpgid: %s", strerror(errno));
		return (ERR_EXEC);
	}
	return (NO_ERROR);
}

static int exec_set_foreground_process_group(pid_t pgid)
{
	if (tcsetpgrp(STDIN_FILENO, pgid) == -1)
	{
		error_set_context("tcsetpgrp: %s", strerror(errno));
		return (ERR_EXEC);
	}
	return (NO_ERROR);
}

void exec_child_set_context(void)
{
	signal_set_ignored_signals_to_default();
	signal_unblock_blocked_signals();
	if (exec_set_process_group_child_side(0, 0) != NO_ERROR)
	{
		error_print("execution: child: failed to set process group");
		_exit(-1);
	}
	if (exec_set_foreground_process_group(getpid()) != NO_ERROR)
	{
		error_print("execution: child: failed to get the controlling terminal");
		exit(-1);
	}
}

int exec_parent_wait_child_process_group(pid_t child_pgid)
{
	int	status;

	if (exec_set_process_group_parent_side(child_pgid, child_pgid) != NO_ERROR)
		error_print("execution: parent: failed to set process group");
	else if (exec_set_foreground_process_group(child_pgid) != NO_ERROR)
		error_print("execution: parent: failed to give the controlling terminal"
				" to the child process");
	status = wait_child_process_group(child_pgid, child_pgid);
	if (exec_set_foreground_process_group(getpid()) != NO_ERROR)
	{
		error_print("execution: parent: failed to get back the controlling"
				"terminal");
		exit(-1);
	}
	return (status);
}
