#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>
#include "exec.h"
#include "errors.h"
#include "ast.h"
#include "array_42.h"

/*
** We use a _control fork_ to launch and monitor the pipeline command.
** The _control fork_ return the exit status for the last command of the pipe
*/

int	exec_node_pipe(const t_ast_node *node, const t_string *input)
{
	pid_t	control_fork;
	int		status;

	assert(node != NULL);
	if (exec_fork(&control_fork) != OK_)
		return (-1);
	if (control_fork == 0)
	{
		exec_child_set_context();
		exec_pipe_sequence(node, input);
		_exit(-1);
	}
	else
		status = exec_parent_wait_child_process_group(control_fork);
	return (status);
}
