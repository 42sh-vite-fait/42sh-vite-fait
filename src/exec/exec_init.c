#include <assert.h>
#include <unistd.h>
#include "opt.h"
#include "errors.h"
#include "exec.h"

static int	dup_fd_to_backup(int fd)
{
	int	fd_copy;

	if (is_fd_open(fd))
	{
		fd_copy = exec_get_backup_fd(fd);
		assert(fd + BACKUP_FD_OFFSET == fd_copy);
		return (exec_backup_fd(fd, fd_copy));
	}
	else
		exec_set_backup_fd(fd, FD_CLOSED);
	return (OK_);
}

static int	backup_tty_fd(void)
{
	int	backup_tty_fd;

	backup_tty_fd = exec_get_backup_fd(BACKUP_TTY_FD);
	if (isatty(STDIN_FILENO))
		return (exec_backup_fd(STDIN_FILENO, backup_tty_fd));
	else if (isatty(STDOUT_FILENO))
		return (exec_backup_fd(STDOUT_FILENO, backup_tty_fd));
	else if (isatty(STDERR_FILENO))
		return (exec_backup_fd(STDERR_FILENO, backup_tty_fd));
	else
		exec_set_backup_fd(BACKUP_TTY_FD, FD_CLOSED);
	return (OK_);
}

int	init_exec_module(void)
{
	if (!is_fd_open(0) && !opt_is_set(OPT_CMD_STRING))
	{
		error_set_context("stdin is closed");
		return (ERROR_);
	}
/*
 * Un fd peut être clos, via <&- >&-
 * Un fd peut pointer vers /dev/null
 * Un fd peut pointer vers un fichier
 * Un fd peut pointer vers un tty
 */
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
