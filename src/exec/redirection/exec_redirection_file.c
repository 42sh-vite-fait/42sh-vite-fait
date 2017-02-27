#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include "exec.h"
#include "errors.h"
#include "stdlib_42.h"

#define OUTPUT_TRUNC (O_WRONLY | O_CREAT | O_TRUNC)
#define OUTPUT_APPEND (O_WRONLY | O_APPEND | O_CREAT)

static int	open_file_and_dup(int io_number, int flags, const char *word)
{
	int	fd;

	fd = open(word, flags, OPEN_DEFAULT_MODE);
	if (fd == -1)
	{
		error_set_context("can't open %s: %s", word, strerror(errno));
		return (ERR_EXEC);
	}
	if (exec_dup_fd(fd, io_number) != NO_ERROR)
		return (ERR_EXEC);
	if (exec_close_fd(fd) != NO_ERROR)
		return (ERR_EXEC);
	return (NO_ERROR);
}

// TODO: Heredoc
// LESS DLESS DLESSDASH
int	exec_redirection_input(int io_number, const char *word)
{
	assert(io_number >= 0 && io_number <= MAX_FD_POSIX_COMPLIANCE);
	return (open_file_and_dup(io_number, O_RDONLY, word));
}

// GREAT CLOBBER
int	exec_redirection_output_trunc(int io_number, const char *word)
{
	assert(io_number >= 0 && io_number <= MAX_FD_POSIX_COMPLIANCE);
	return (open_file_and_dup(io_number, OUTPUT_TRUNC, word));
}

// DGREAT
int	exec_redirection_output_append(int io_number, const char *word)
{
	assert(io_number >= 0 && io_number <= MAX_FD_POSIX_COMPLIANCE);
	return (open_file_and_dup(io_number, OUTPUT_APPEND, word));
}
