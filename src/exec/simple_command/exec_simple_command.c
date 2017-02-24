#include "exec.h"
#include "ast.h"
#include "errors.h"

int exec_simple_command_binary(const t_command command)
{
	pid_t	child;
	int		status;

	child = fork();
	if (child == -1)
	{
		error_set_context("fork: %s", strerror(errno));
		status = ERR_EXEC;
	}
	else if (child == 0)
	{
		signal(SIGTTOU, SIG_DFL); // TODO: module signal
		if (exec_process_group_child_side(0, 0) != NO_ERROR)
			_exit(ERR_EXEC);
		exec_binary(command);
		status = -1;
	}
	else
	{
		if (exec_process_group_parent_side(child, child) != NO_ERROR
				|| exec_set_foreground_process_group(child) != NO_ERROR)
			return (ERR_EXEC);
		status = wait_for_children(child, child);
		if (exec_set_foreground_process_group(getpid()) != NO_ERROR)
			return (ERR_EXEC);
	}
	return (status);
}

int exec_simple_command_builtin(const t_command command)
{
	(void)command;
	return (-1);
}
