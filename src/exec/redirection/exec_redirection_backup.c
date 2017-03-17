#include <unistd.h>
#include <fcntl.h>
#include <sys/resource.h>
#include "errors.h"
#include "exec.h"

#define MAX_FD_TO_DUP 	(3)
#define BACKUP_OFFSET	(10)

static int	g_backup_standard_fd[3];

static int	get_limit_max_open_files(struct rlimit *limit)
{
	if (getrlimit(RLIMIT_NOFILE, limit) == -1)
	{
		error_set_context("getrlimit: %s", strerror(errno));
		return (ERR_EXEC);
	}
	return (OK_);
}

static int	increase_open_files_limit(void)
{
	struct rlimit	limit;

	if (get_limit_max_open_files(&limit) != OK_)
		return (ERR_EXEC);
	if (limit.rlim_max < MAX_FD_TO_DUP + BACKUP_OFFSET)
	{
		error_set_context("limit max fd too low: %d", (int)limit.rlim_max);
		return (ERR_EXEC);
	}
	if (limit.rlim_cur < MAX_FD_TO_DUP + BACKUP_OFFSET)
	{
		limit.rlim_cur = limit.rlim_max;
		if (setrlimit(RLIMIT_NOFILE, &limit) == -1)
		{
			error_set_context("setrlimit: %s", strerror(errno));
			return (ERR_EXEC);
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
		return (ERR_EXEC);
	}
	flags |= FD_CLOEXEC;
	if (fcntl(fd, F_SETFD, flags) == -1)
	{
		error_set_context("fcntl: %s", strerror(errno));
		return (ERR_EXEC);
	}
	return (OK_);
}

int	exec_backup_standard_fd(void)
{
	int	ret;
	int	i;

	ret = increase_open_files_limit();
	if (ret != OK_)
		return (ret);
	i = 0;
	while (i < MAX_FD_TO_DUP)
	{
		g_backup_standard_fd[i] = BACKUP_OFFSET + i;
		if (exec_dup_fd(i, g_backup_standard_fd[i]) != OK_)
			return (ERR_EXEC);
		if (set_close_on_exec_flag(g_backup_standard_fd[i]) != OK_)
			return (ERR_EXEC);
		i += 1;
	}
	return (OK_);
}

int	exec_backup_get_standard_fd(size_t n)
{
	return (g_backup_standard_fd[n]);
}
