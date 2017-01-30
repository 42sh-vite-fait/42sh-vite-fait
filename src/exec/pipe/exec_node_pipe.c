#include <unistd.h>
#include <assert.h>
#include "exec.h"
#include "errors.h"
#include "ast.h"
#include "array_42.h"

int	exec_node_pipe(const t_ast_node *node)
{
	int	pid;
	int	status;

	assert(node != NULL);
	pid = fork();
	if (pid == -1)
	{
		error_set_context("fork: %s", strerror(errno));
		return (-1);
	}
	else if (pid == 0)
	{
		if (exec_process_group(0, 0) != NO_ERROR)
			_exit(EXIT_FAILURE);
		exec_pipe_sequence(node);
	}
	if (exec_process_group_create(pid, pid) != NO_ERROR)
		return (-1);
	waitpid(pid, &status, 0); // On attend le fork de controle
	// TODO: tester retours
	return (status);
}

// exec_pipe_command -> (launch builtin + exit after builtin completion)
//                   -> (launch binary)
