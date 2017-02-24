#include "exec.h"
#include "ast.h"
#include "errors.h"

static void	exec_child_command(const t_command command)
{
	signal(SIGTTOU, SIG_DFL); // TODO: module signal
	if (exec_set_process_group_child_side(0, 0) != NO_ERROR)
	{
		error_print("execution: child: failed to set process group");
		_exit(ERR_EXEC);
	}
	exec_binary(command);
}

static int	exec_parent_wait(pid_t child)
{
	int	status;

	if (exec_set_process_group_parent_side(child, child) != NO_ERROR)
		error_print("execution: parent: failed to set process group");
	else if (exec_set_foreground_process_group(child) != NO_ERROR)
		error_print("execution: parent: failed to give the controlling terminal"
				"to the child process");
	status = wait_for_children(child, child);
	if (exec_set_foreground_process_group(getpid()) != NO_ERROR)
	{
		error_print("execution: parent: failed to get back the controlling"
				"terminal");
		exit(-1);
	}
	return (status);
}

int exec_simple_command_binary(const t_command command)
{
	pid_t	child;
	int		status;

	if (exec_fork(&child) != NO_ERROR)
		return (-1);
	if (child == 0)
		exec_child_command(command);
	else
		status = exec_parent_wait(child);
	return (status);
}

int exec_simple_command_builtin(const t_command command)
{
	(void)command;
	return (0);
}
