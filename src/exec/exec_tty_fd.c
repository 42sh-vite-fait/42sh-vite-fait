#include <assert.h>
#include <unistd.h>
#include "exec.h"

static int	g_backup_fd[] = {
	[STDIN_FILENO] = BACKUP_FD_OFFSET + STDIN_FILENO,
	[STDOUT_FILENO] = BACKUP_FD_OFFSET + STDOUT_FILENO,
	[STDERR_FILENO] = BACKUP_FD_OFFSET + STDERR_FILENO,
	[BACKUP_TTY_FD] = BACKUP_FD_OFFSET + BACKUP_TTY_FD,
};

int		exec_get_backup_fd(unsigned n)
{
	return (g_backup_fd[n]);
}

void	exec_set_backup_fd(unsigned index, int new_fd)
{
	g_backup_fd[index] = new_fd;
}
