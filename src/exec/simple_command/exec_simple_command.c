#include "exec.h"
#include "ast.h"
#include "errors.h"

/*
** Return values:
**	execve error, -1
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
		status = -1;
	}
	else if (pid == 0)
	{
		if (exec_process_group_create(0, 0) != NO_ERROR)
			return (-1);
		exec_binary(command);
		status = -1;
	}
	else
	{
		if (exec_process_group_create(pid, pid) != NO_ERROR)
			return (-1);
		status = wait_for_children(pid, pid);
	}
	return (status);
}

int exec_simple_command_builtin(const t_command command)
{
	(void)command;
	return (-1);
}
