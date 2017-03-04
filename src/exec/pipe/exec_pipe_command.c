#include "expansion.h"
#include "var.h"
#include "exec.h"
#include "array_42.h"
#include "builtins.h"

static void	exec_pipe_wrapper_builtin(const t_command command,
		const t_string *input)
{
	t_array			argv;
	char * const	*envp;
	int				status;

	if (exec_redirection(command.redirections, input) != NO_ERROR)
	{
		error_print("execution");
		_exit(-1);
	}
	argv = expand_tokens_to_argv(command.words, input);
	envp = var_get_environ();
	status = exec_builtin(argv.len, argv.data, envp);
	_exit(status);
}

void	exec_pipe_command(const t_command command, const t_string *input)
{
	t_token	*token;

	token = *(t_token**)array_get_first(&command.words);
	if (is_builtin(input->str + token->start, token->len))
		exec_pipe_wrapper_builtin(command, input);
	else
		exec_binary(command, input);
}
