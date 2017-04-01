#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include "exec.h"
#include "lexer.h"
#include "errors.h"

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
		if (devnull == -1 || exec_dup_fd(devnull, io_number) != OK_)
			return (ERROR_);
		exec_close_fd(devnull);
	}
	else
		return (exec_close_fd(io_number));
	return (OK_);
}

static int	duplicate_fd(int io_number, unsigned word)
{
	assert(word <= E_MAX_FD_POSIX_COMPLIANCE);
	if (!is_fd_open(word))
	{
		error_set_context("%d: %s", word, strerror(errno));
		return (ERROR_);
	}
	else
	   return (exec_dup_fd(word, io_number) != OK_);
}

static int	exec_redirection_dup(int io_number, const char *word)
{
	int	ret;

	if (ft_strcmp(word, "-") == 0)
		ret = close_fd(io_number);
	else if (is_only_one_digit(word))
		ret = duplicate_fd(io_number, ft_atou(word));
	else
	{
		error_set_context("%s: illegal file descriptor name", word);
		ret = ERROR_;
	}
	return (ret);
}

// LESSAND
int	exec_redirection_input_duplicate(int io_number, const char *word)
{
	assert(io_number >= 0 && io_number <= E_MAX_FD_POSIX_COMPLIANCE);
	return (exec_redirection_dup(io_number, word));
}

// GREATAND
int	exec_redirection_output_duplicate(int io_number, const char *word)
{
	assert(io_number >= 0 && io_number <= E_MAX_FD_POSIX_COMPLIANCE);
	return (exec_redirection_dup(io_number, word));
}
