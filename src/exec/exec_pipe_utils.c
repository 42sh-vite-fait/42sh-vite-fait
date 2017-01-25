#include <unistd.h>
#include "exec.h"
#include "errors.h"

/* int	pipe_connect_write_end(int write_end) */
int	pipe_replace_stdout(int write_end)
{
	if (dup2(write_end, STDOUT_FILENO) == -1)
		return (ERR_DUP2);
	return (NO_ERROR);
}

/* int	pipe_connect_read_end(int read_end) */
int	pipe_replace_stdin(int read_end)
{
	if (dup2(read_end, STDIN_FILENO) == -1)
		return (ERR_DUP2);
	return (NO_ERROR);
}

int pipe_replace_stdfd(int read_end, int write_end)
{
	if (dup2(write_end, STDOUT_FILENO) == -1)
		return (ERR_DUP2);
	if (dup2(read_end, STDIN_FILENO) == -1)
		return (ERR_DUP2);
	return (NO_ERROR);
}

int	pipe_init(t_pipe *pype)
{
	int	p[2];

	if (pipe(p) == -1)
	{
		error_set_context("pipe: %s", strerror(errno));
		return (-1);
	}
	pype->read = p[0];
	pype->write = p[1];
	return (0);
}

