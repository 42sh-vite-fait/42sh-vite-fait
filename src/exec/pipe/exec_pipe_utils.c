#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <signal.h>
#include "exec.h"
#include "errors.h"

int		pipe_replace_stdout(int write_end)
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
	return (OK_);
}

int		pipe_replace_stdin(int read_end)
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
	return (OK_);
}

int		pipe_init(t_pipe *pype)
{
	int	p[2];

	if (pipe(p) == -1)
	{
		error_set_context("pipe function: %s", strerror(errno));
		return (ERR_EXEC);
	}
	pype->read = p[0];
	pype->write = p[1];
	return (OK_);
}

void	pipe_kill_pipe_sequence(void)
{
	error_print("execution: pipe");
	kill(0, SIGABRT);
}
