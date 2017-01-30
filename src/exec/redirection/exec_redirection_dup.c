#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include "exec.h"
#include "lexer.h"
#include "errors.h"

#define FAM_READING (O_RDWR | O_RDONLY)
#define FAM_WRITING (O_RDWR | O_WRONLY)
#define MAX_FD_POSIX_COMPLIANCE (9)

/*
** See the Rationale for the explanation of why dup2 on /dev/null
** [http://pubs.opengroup.org/onlinepubs/9699919799/xrat/V4_xcu_chap02.html]
*/

static int	close_fd(int io_number)
{
	int	fd;

	if (IS_FD_STANDARD(io_number))
	{
		fd = open("/dev/null", O_RDWR, 0666);
		if (fd == -1)
			return (ERR_EXEC);
		if (dup2(io_number, fd) == -1)
			return (ERR_EXEC);
	}
	else
		close(io_number);
	return (NO_ERROR);
}

static int	duplicate_fd(int io_number, int mode, int word)
{
	int	flags;

	if (word > MAX_FD_POSIX_COMPLIANCE)
		return (ERR_EXEC);
	flags = fcntl(word, F_GETFL);
	if (flags == -1)
		return (ERR_EXEC);
	if (flags & mode)
	{
		if (dup2(io_number, word) == -1)
			return (ERR_EXEC);
	}
	else
		return (ERR_EXEC);
	return (NO_ERROR);
}

static int	exec_redirection_dup(int io_number, int mode, const char *word)
{
	int	ret;

	if (word[0] == '-' && word[1] == '\0')
		ret = close_fd(io_number);
	else if (is_only_one_digit(word))
		ret = duplicate_fd(io_number, mode, (int)ft_atou(word)); // TODO: error
	else
		ret = ERR_EXEC;
	return (ret);
}

// LESSAND
int	exec_redirection_input_duplicate(int io_number, const char *word)
{
	assert(io_number >= 0);
	return (exec_redirection_dup(io_number, FAM_READING, word));
}

// GREATAND
int	exec_redirection_output_duplicate(int io_number, const char *word)
{
	assert(io_number >= 0);
	return (exec_redirection_dup(io_number, FAM_WRITING, word));
}
