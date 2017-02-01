#include "exec.h"
#include "ast.h"
#include "expansion.h"
#include "var.h"

#define BACKUP_PATH ("")

void exec_binary(const t_command command)
{
	const char		*paths;
	char * const	*argv;
	char * const	*envp;

	if (exec_redirection(command.redirections) != NO_ERROR)
	{
		error_print("execution");
		_exit(-1);
	}
	// signal_set_for_exec();

	if (var_get("PATH", &paths) != NO_ERROR)
		paths = BACKUP_PATH;
	argv = expand_tokens_to_argv(command.words);
	envp = var_get_environ();
	exec_with_path(paths, argv, envp);
}
