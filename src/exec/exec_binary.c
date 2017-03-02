#include "expansion.h"
#include "exec.h"
#include "ast.h"
#include "var.h"

#define BACKUP_PATH ("")

/*
** This function should never return in case of failure !
*/

void exec_binary(const t_command command)
{
	const char		*paths;
	t_array			argv;
	char * const	*envp;

	if (exec_redirection(command.redirections) != NO_ERROR)
	{
		error_print("execution");
		_exit(-1);
	}
	if (var_get("PATH", &paths) != NO_ERROR)
		paths = BACKUP_PATH;
	argv = expand_tokens_to_argv(command.words);
	envp = var_get_environ();
	exec_with_path(paths, argv.data, envp);
}
