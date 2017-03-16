#include "expansion.h"
#include "var.h"
#include "exec.h"
#include "ast.h"
#include "errors.h"
#include "builtins.h"

int exec_simple_command_binary(const t_command command, const t_string *input)
{
	pid_t	child;
	int		status;

	if (exec_fork(&child) != NO_ERROR)
		return (-1);
	if (child == 0)
	{
		exec_child_set_context();
		exec_binary(command, input);
		_exit(-1);
	}
	else
		status = exec_parent_wait_child_process_group(child);
	return (status);
}

static void	free_args(t_array	*argv)
{
	size_t	i;

	i = 0;
	while (i < argv->len)
	{
		free(*(void **)array_get_at(argv, i));
		i += 1;
	}
	array_shutdown(argv);
}

int exec_simple_command_builtin(const t_command command, const t_string *input)
{
	t_array			argv;
	int				status;

	if (exec_redirection(command.redirections, input) != NO_ERROR)
	{
		error_print("execution");
		return (-1);
	}
	argv = expand_tokens_to_argv(command.words, input);
	status = exec_builtin(argv.len, argv.data);
	free_args(&argv);
	if (undo_redirection(command.redirections) != NO_ERROR)
		error_print("execution");
	return (status);
}
