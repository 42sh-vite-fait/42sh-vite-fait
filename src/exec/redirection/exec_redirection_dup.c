#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include "exec.h"
#include "lexer.h"
#include "errors.h"

#define READING_MODE (O_RDWR | O_RDONLY)
#define WRITING_MODE (O_RDWR | O_WRONLY)

/*
** See the Rationale for the explanation of why dup2 on /dev/null
** [http://pubs.opengroup.org/onlinepubs/9699919799/xrat/V4_xcu_chap02.html]
*/

static int	close_fd(int io_number)
{
	int	devnull;

	if (IS_FD_STANDARD(io_number))
	{
		devnull = open("/dev/null", O_RDWR, OPEN_DEFAULT_MODE);
		if (devnull == -1 || exec_dup_fd(devnull, io_number) != NO_ERROR)
			return (ERR_EXEC);
	}
	else
		return (exec_close_fd(io_number));
	return (NO_ERROR);
}

static int	duplicate_fd(int io_number, int mode, unsigned word)
{
	int	flags;

	assert(word <= MAX_FD_POSIX_COMPLIANCE);
	flags = fcntl(word, F_GETFL);
	if (flags == -1)
	{
		error_set_context("%d: %s", word, strerror(errno));
		return (ERR_EXEC);
	}
	else if (flags & mode)
		return (exec_dup_fd(word, io_number));
	else
	{
		error_set_context("%d: access mode invalid", word);
		return (ERR_EXEC);
	}
}

static int	exec_redirection_dup(int io_number, int mode, const char *word)
{
	int	ret;

	if (ft_strcmp(word, "-") == 0)
		ret = close_fd(io_number);
	else if (is_only_one_digit(word))
		ret = duplicate_fd(io_number, mode, ft_atou(word));
	else
	{
		error_set_context("%s: illegal file descriptor name", word);
		ret = ERR_EXEC;
	}
	return (ret);
}

// LESSAND
int	exec_redirection_input_duplicate(int io_number, const char *word)
{
	assert(io_number >= 0 && io_number <= MAX_FD_POSIX_COMPLIANCE);
	return (exec_redirection_dup(io_number, READING_MODE, word));
}

// GREATAND
int	exec_redirection_output_duplicate(int io_number, const char *word)
{
	assert(io_number >= 0 && io_number <= MAX_FD_POSIX_COMPLIANCE);
	return (exec_redirection_dup(io_number, WRITING_MODE, word));
}
