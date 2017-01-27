#include <unistd.h>
#include <fcntl.h>
#include <sys/resource.h>
#include "errors.h"

#define MAX_FD (3)
#define BACKUP_OFFSET	(10)

static int	g_backup_standard_fd[3];

static int	check_and_bump_open_files_limit(void)
{
	struct rlimit	limit;
	
	if (getrlimit(RLIMIT_NOFILE, &limit) == -1)
		return (ERR_GRLIMIT);
	if (limit.rlim_max < MAX_FD + BACKUP_OFFSET)
		return (ERR_FDLIMIT);
	if (limit.rlim_cur < MAX_FD + BACKUP_OFFSET)
	{
		limit.rlim_cur = limit.rlim_max;
		if (setrlimit(RLIMIT_NOFILE, &limit) == -1)
			return (ERR_SRLIMIT);
	}
	return (NO_ERROR);
}

static int	set_close_on_exec_flag(int fd)
{
	int	flags;

	flags = fcntl(fd, F_GETFD);
	if (flags == -1)
		return (ERR_FCNTL);
	flags |= FD_CLOEXEC;
	if (fcntl(fd, F_SETFD, flags) == -1)
		return (ERR_FCNTL);
	return (NO_ERROR);
}

static int	backup_standard_fd(void)
{
	int	ret;
	int	i;

	ret = check_and_bump_open_files_limit();
	if (ret != NO_ERROR)
		return (ret);
	i = 0;
	while (i < MAX_FD)
	{
		g_backup_standard_fd[i] = dup2(i, BACKUP_OFFSET + i);
		if (g_backup_standard_fd[i] == -1)
			return (ERR_DUP2);
		if (set_close_on_exec_flag(g_backup_standard_fd[i]) != NO_ERROR)
			return (ERR_FCNTL);
		i += 1;
	}
	return (NO_ERROR);
}

int	get_backup_standard_fd(size_t n)
{
	return (g_backup_standard_fd[n]);
}

int	startup_redirection_init(void)
{
	int	ret;
	
	if ((ret = backup_standard_fd()) != NO_ERROR)
		return (ret);
	return (NO_ERROR);
}