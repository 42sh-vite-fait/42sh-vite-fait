#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>
#include "exec.h"
#include "errors.h"
#include "ast.h"
#include "array_42.h"

static void	exec_control_fork(const t_ast_node *node)
{
	// TODO: factorize en set_child_context
	signal(SIGTTOU, SIG_DFL); // TODO: module signal
	if (exec_set_process_group_child_side(0, 0) != NO_ERROR)
	{
		error_print("execution: failed to create child's process group");
		_exit(ERR_EXEC);
	}
	exec_pipe_sequence(node);
}

static int	exec_parent_wait_control_fork(pid_t child)
{
	int	status;

	if (exec_set_process_group_parent_side(child, child) != NO_ERROR)
		return (-1);
	if (exec_set_foreground_process_group(child) != NO_ERROR)
		return (-1);
	status = wait_for_children(child, child);
	if (exec_set_foreground_process_group(getpid()) != NO_ERROR)
	{
		error_print("execution: failed to attach to the controlling terminal");
		exit(-1);
	}
	return (status);
}

/*
** We use a _control fork_ to launch and monitor the pipeline command.
** The _control fork_ return the exit status for the last command of the pipe
*/

int	exec_node_pipe(const t_ast_node *node)
{
	pid_t	control_fork;
	int		status;

	assert(node != NULL);
	if (exec_fork(&control_fork) != NO_ERROR)
		status = -1;
	if (control_fork == 0)
		exec_control_fork(node);
	else
		status = exec_parent_wait_control_fork(control_fork);
	return (status);
}
