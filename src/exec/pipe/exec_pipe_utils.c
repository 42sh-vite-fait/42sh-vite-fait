#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include "exec.h"
#include "errors.h"

int		pipe_replace_stdout(int write_end)
{
	if (dup2(write_end, STDOUT_FILENO) == -1)
	{
		error_set_context("dup2: %s", strerror(errno));
		return (ERROR_);
	}
	if (close(write_end) == -1)
	{
		error_set_context("close: %s", strerror(errno));
		return (ERROR_);
	}
	return (OK_);
}

int		pipe_replace_stdin(int read_end)
{
	if (dup2(read_end, STDIN_FILENO) == -1)
	{
		error_set_context("dup2: %s", strerror(errno));
		return (ERROR_);
	}
	if (close(read_end) == -1)
	{
		error_set_context("close: %s", strerror(errno));
		return (ERROR_);
	}
	return (OK_);
}

static int	pipe_dup_first_free_fd(int pipe_fd)
{
	int	i;

	i = E_PIPE_UTIL;
	while (is_fd_open(i))
		i += 1;
	assert(i >= E_PIPE_UTIL && i < E_MAX_FD_NEEDED);
	exec_dup_fd(pipe_fd, i);
	exec_close_fd(pipe_fd);
	return (i);
}

int		pipe_init(t_pipe *pype)
{
	int	p[2];

	if (pipe(p) == -1)
	{
		error_set_context("pipe function: %s", strerror(errno));
		return (ERROR_);
	}
	pype->read = pipe_dup_first_free_fd(p[0]);
	pype->write = pipe_dup_first_free_fd(p[1]);
	return (OK_);
}

void	pipe_kill_pipe_sequence(void)
{
	error_print("execution: pipe");
	kill(0, SIGABRT);
}
