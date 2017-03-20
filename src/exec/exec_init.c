#include <assert.h>
#include <unistd.h>
#include <sys/resource.h>
#include "opt.h"
#include "errors.h"
#include "exec.h"

static int	increase_open_files_limit(unsigned max_fd)
{
	struct rlimit	limit;

	if (getrlimit(RLIMIT_NOFILE, &limit) == -1)
	{
		error_set_context("getrlimit: %s", strerror(errno));
		return (ERROR_);
	}
	if (limit.rlim_max < max_fd)
	{
		error_set_context("limit max fd too low: %d", (int)limit.rlim_max);
		return (ERROR_);
	}
	if (limit.rlim_cur < max_fd)
	{
		limit.rlim_cur = max_fd;
		if (setrlimit(RLIMIT_NOFILE, &limit) == -1)
		{
			error_set_context("setrlimit: %u: %s", max_fd, strerror(errno));
			return (ERROR_);
		}
	}
	return (OK_);
}

static int	dup_fd_to_backup(int fd)
{
	int	fd_copy;

	fd_copy = fd + E_FD_BACKUP_OFFSET;
	if (is_fd_open(fd))
		return (exec_backup_fd(fd, fd_copy));
	return (OK_);
}

static int	backup_tty_fd(void)
{
	if (isatty(STDIN_FILENO))
		return (exec_backup_fd(STDIN_FILENO, E_TTY_FD));
	else if (isatty(STDOUT_FILENO))
		return (exec_backup_fd(STDOUT_FILENO, E_TTY_FD));
	else if (isatty(STDERR_FILENO))
		return (exec_backup_fd(STDERR_FILENO, E_TTY_FD));
	return (OK_);
}

int	init_exec_module(void)
{
	if (!is_fd_open(STDIN_FILENO) && !opt_is_set(OPT_CMD_STRING))
	{
		error_set_context("stdin is closed");
		return (ERROR_);
	}
	if (increase_open_files_limit(E_MAX_FD_NEEDED) != OK_)
		return (ERROR_);
	if (dup_fd_to_backup(STDIN_FILENO) != OK_)
		return (ERROR_);
	if (dup_fd_to_backup(STDOUT_FILENO) != OK_)
		return (ERROR_);
	if (dup_fd_to_backup(STDERR_FILENO) != OK_)
		return (ERROR_);
	if (backup_tty_fd() != OK_)
		return (ERROR_);
	return (OK_);
}
