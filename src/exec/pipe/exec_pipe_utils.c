#include <unistd.h>
#include "exec.h"
#include "errors.h"

int	pipe_replace_stdout(int write_end)
{
	if (dup2(write_end, STDOUT_FILENO) == -1)
	{
		error_set_context("dup2: %s", strerror(errno));
		return (ERR_EXEC);
	}
	if (close(write_end) == -1)
	{
		error_set_context("close: %s", strerror(errno));
		return (ERR_EXEC);
	}
	return (NO_ERROR);
}

int	pipe_replace_stdin(int read_end)
{
	if (dup2(read_end, STDIN_FILENO) == -1)
	{
		error_set_context("dup2: %s", strerror(errno));
		return (ERR_EXEC);
	}
	if (close(read_end) == -1)
	{
		error_set_context("close: %s", strerror(errno));
		return (ERR_EXEC);
	}
	return (NO_ERROR);
}

int	pipe_init(t_pipe *pype)
{
	int	p[2];

	if (pipe(p) == -1)
	{
		error_set_context("pipe: %s", strerror(errno));
		return (ERR_EXEC);
	}
	pype->read = p[0];
	pype->write = p[1];
	return (NO_ERROR);
}

void	pipe_exit_on_child_error(void)
{
	error_print("pipe");
	// TODO: kill process group
	_exit(EXIT_FAILURE);
}
