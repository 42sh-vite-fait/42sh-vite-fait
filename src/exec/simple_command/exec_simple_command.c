#include "exec.h"
#include "ast.h"
#include "errors.h"

/*
** Returned values:
**	builtin, value return by the builtin execution
**	binary, nothing (process image is replaced)
*/

int exec_simple_command_binary(const t_command command)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		error_set_context("fork: %s", strerror(errno));
		status = ERR_EXEC;
	}
	else if (pid == 0)
	{
		signal(SIGTTOU, SIG_DFL); // TODO: module signal
		if (exec_process_group_child_side(0, 0) != NO_ERROR)
			_exit(ERR_EXEC);
		exec_binary(command);
	}
	else
	{
		if (exec_process_group_parent_side(pid, pid) != NO_ERROR)
			return (ERR_EXEC);
		tcsetpgrp(STDIN_FILENO, pid);
		status = wait_for_children(pid, pid);
		tcsetpgrp(STDIN_FILENO, getpid());
	}
	return (status);
}

int exec_simple_command_builtin(const t_command command)
{
	(void)command;
	return (-1);
}
