#include <unistd.h>
#include "opt.h"
#include "exec.h"

#define MAX_FD_TO_BACKUP 	(3)
#define BACKUP_OFFSET		(10)
#define BACKUP_TTY_FD		(4)

static const int	g_standard_fd[] = {
	[STDIN_FILENO] = BACKUP_OFFSET + STDIN_FILENO,
	[STDOUT_FILENO] = BACKUP_OFFSET + STDOUT_FILENO,
	[STDERR_FILENO] = BACKUP_OFFSET + STDERR_FILENO,
};
static const int	g_tty_fd = BACKUP_OFFSET + BACKUP_TTY_FD;

int	init_exec_fd(void)
{
	if (exec_backup_fd(0, g_standard_fd[0]) != OK_
			|| exec_backup_fd(1, g_standard_fd[1]) != OK_
			|| exec_backup_fd(2, g_standard_fd[2]) != OK_)
		return (ERROR_);
	if (opt_is_set(OPT_INTERACTIVE) && exec_backup_fd(0, g_tty_fd) != OK_)
		return (ERROR_);
	return (OK_);
}

int	exec_get_tty_fd()
{
	return (g_tty_fd);
}

int	exec_get_standard_fd(unsigned n)
{
	return (g_standard_fd[n]);
}
