#include <unistd.h>
#include <fcntl.h>
#include "exec.h"
#include "errors.h"
#include "stdlib_42.h"

#define DEFAULT_MODE (0644)
#define OUTPUT_TRUNC (O_WRONLY | O_CREAT | O_TRUNC)
#define OUTPUT_APPEND (O_WRONLY | O_APPEND)

static int	open_file_and_dup(int io_number, int flags, const char *word)
{
	int	fd;

	fd = open(word, flags, DEFAULT_MODE);
	if (fd == -1)
	{
		error_set_context("open: %s", strerror(errno));
		return (ERR_EXEC);
	}
	if (exec_dup_fd(io_number, fd) == -1)
		return (ERR_EXEC);
	if (exec_close_fd(fd) == 1)
		return (ERR_EXEC);
	return (NO_ERROR);
}

// TODO: Heredoc
// LESS DLESS DLESSDASH
int	exec_redirection_input(int io_number, const char *word)
{
	return (open_file_and_dup(io_number, O_RDONLY, word));
}

// GREAT CLOBBER
int	exec_redirection_output_trunc(int io_number, const char *word)
{
	return (open_file_and_dup(io_number, OUTPUT_TRUNC, word));
}

// DGREAT
int	exec_redirection_output_append(int io_number, const char *word)
{
	return (open_file_and_dup(io_number, OUTPUT_APPEND, word));
}
