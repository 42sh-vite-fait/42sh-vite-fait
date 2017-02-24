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

	signal(SIGTTOU, SIG_IGN); // TODO: pourquoi ?
	pid = fork();
	if (pid == -1)
	{
		error_set_context("fork: %s", strerror(errno));
		status = -1;
	}
	else if (pid == 0)
	{
		signal(SIGTTOU, SIG_DFL);
		if (exec_process_group_child_side(0, 0) != NO_ERROR)
			_exit(-1);
		exec_binary(command);
		status = -1;
	}
	else
	{
		if (exec_process_group_parent_side(pid, pid) != NO_ERROR)
			return (-1);
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
