#include <unistd.h>
#include "exec.h"
#include "errors.h"
#include "ast.h"
#include "array_42.h"

int	exec_node_pipe(const t_ast_node *node)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		error_set_context("fork: %s", strerror(errno));
	else if (pid == 0)
	{
		exec_node_pipe(node);
	}
	setpgid(pid, pid);
	waitpid(pid, &status, 0); // On attend le fork de controle
	// TODO: tester retours
	return (status);
}

// exec_pipe_command -> (launch builtin + exit after builtin completion)
//                   -> (launch binary)
