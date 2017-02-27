#include "expansion.h"
#include "var.h"
#include "exec.h"
#include "ast.h"
#include "errors.h"
#include "builtins.h"

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
	t_array			argv;
	char * const	*envp;
	int				status;

	if (exec_redirection(command.redirections) != NO_ERROR)
	{
		error_print("execution");
		return (-1);
	}
	argv = expand_tokens_to_argv(command.words);
	envp = var_get_environ();
	status = exec_builtin(argv.len, argv.data, envp);
	if (undo_redirection(command.redirections) != NO_ERROR)
		error_print("execution");
	return (status);
}
