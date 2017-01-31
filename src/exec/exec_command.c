#include "exec.h"
#include "ast.h"
#include "expansion.h"

void exec_binary(const t_command command)
{
	char * const	*argv;
	if (exec_redirection(command.redirections) != NO_ERROR)
	{
		error_print("execution");
		_exit(-1);
	}
	// signal_set_for_exec();

	/* paths = variable_get_path(); */
	argv = expand_tokens_to_argv(command.words);
	/* envp = variable_export_environ(); */
	exec_with_path(paths, argv, envp);
}
