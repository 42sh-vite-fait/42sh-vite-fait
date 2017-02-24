#include "exec.h"
#include "array_42.h"
#include "builtins.h"

static void	exec_pipe_wrapper_builtin(const t_command command)
{
	(void)command;
	// TODO: redirections
	// TODO: execution builtin
	_exit(0);
}

void	exec_pipe_command(const t_command command)
{
	t_token	*token;

	token = array_get_first(&command.words);
	if (is_builtin(token->str, token->len))
		exec_pipe_wrapper_builtin(command);
	else
		exec_binary(command);
}
