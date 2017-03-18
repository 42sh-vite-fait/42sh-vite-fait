#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/resource.h>
#include "errors.h"
#include "exec.h"

static int	get_limit_max_open_files(struct rlimit *limit)
{
	if (getrlimit(RLIMIT_NOFILE, limit) == -1)
	{
		error_set_context("getrlimit: %s", strerror(errno));
		return (ERROR_);
	}
	return (OK_);
}

static int	increase_open_files_limit(unsigned fd)
{
	struct rlimit	limit;

	if (get_limit_max_open_files(&limit) != OK_)
		return (ERROR_);
	if (limit.rlim_max < fd)
	{
		error_set_context("limit max fd too low: %d", (int)limit.rlim_max);
		return (ERROR_);
	}
	if (limit.rlim_cur < fd)
	{
		limit.rlim_cur = limit.rlim_max;
		if (setrlimit(RLIMIT_NOFILE, &limit) == -1)
		{
			error_set_context("setrlimit: %s", strerror(errno));
			return (ERROR_);
		}
	}
	return (OK_);
}

static int	set_close_on_exec_flag(int fd)
{
	int	flags;

	flags = fcntl(fd, F_GETFD);
	if (flags == -1)
	{
		error_set_context("fcntl: %s", strerror(errno));
		return (ERROR_);
	}
	flags |= FD_CLOEXEC;
	if (fcntl(fd, F_SETFD, flags) == -1)
	{
		error_set_context("fcntl: %s", strerror(errno));
		return (ERROR_);
	}
	return (OK_);
}

int			exec_backup_fd(int fd, int new_fd)
{
	assert(fd >= 0);
	if (increase_open_files_limit(new_fd) != OK_)
		return (ERROR_);
	if (exec_dup_fd(fd, new_fd) != OK_)
		return (ERROR_);
	if (set_close_on_exec_flag(new_fd) != OK_)
		return (ERROR_);
	return (OK_);
}
