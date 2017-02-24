#include "exec.h"
#include "ast.h"
#include "errors.h"

int exec_simple_command_binary(const t_command command)
{
	pid_t	child;
	int		status;

	if (exec_fork(&child) != NO_ERROR)
		return (-1);
	if (child == 0)
	{
		exec_child_set_context();
		exec_binary(command);
		_exit(-1);
	}
	else
		status = exec_parent_wait_child_process_group(child);
	return (status);
}

int exec_simple_command_builtin(const t_command command)
{
	(void)command;
	return (0);
}
