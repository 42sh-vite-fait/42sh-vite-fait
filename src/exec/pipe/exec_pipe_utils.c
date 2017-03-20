#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <signal.h>
#include "exec.h"
#include "errors.h"

int		pipe_replace_stdout(int write_end)
{
	if (dup2(write_end, STDOUT_FILENO) == -1)
	{
		error_set_context("dup2: %s", strerror(errno));
		return (ERROR_);
	}
	if (close(write_end) == -1)
	{
		error_set_context("close: %s", strerror(errno));
		return (ERROR_);
	}
	return (OK_);
}

int		pipe_replace_stdin(int read_end)
{
	if (dup2(read_end, STDIN_FILENO) == -1)
	{
		error_set_context("dup2: %s", strerror(errno));
		return (ERROR_);
	}
	if (close(read_end) == -1)
	{
		error_set_context("close: %s", strerror(errno));
		return (ERROR_);
	}
	return (OK_);
}

int		pipe_init(t_pipe *pype)
{
	int	p[2];

	if (pipe(p) == -1)
	{
		error_set_context("pipe function: %s", strerror(errno));
		return (ERROR_);
	}

	/*
	 * Le probleme vient du fait que si des fds standard sont fermés
	 * au lancement du shell, alors la creation de pipe peut les overlaps
	 * Ce qui devient chiant quand on fait le linkage (dup/close)
	 * La solution (?) est de dup les fds du pipe dés leurs creations
	 * vers des numeros au-dessus de 13.
	 * On verifie si le fd est open, si il ne l'est pas, on dup
	 *
	 * Ne pas oublier d'augmenter la limite soft des fds open
	 * Faire le tests d'afficher les fds des pipes apres dup pour voir le cycle
	 * ./42sh -c 'env | cat -e | wc | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e' <&- >&- 2>&- 11>file
	 */
	if (IS_FD_STANDARD(p[0]))
	{
		int i;
		for (i = E_PIPE_UTIL; is_fd_open(i); ++i)
			;
		exec_dup_fd(p[0], i);
		exec_close_fd(p[0]);
		pype->read = i;
	}
	else
		pype->read = p[0];

	if (IS_FD_STANDARD(p[1]))
	{
		int i;
		for (i = E_PIPE_UTIL; is_fd_open(i); ++i)
			;
		exec_dup_fd(p[1], i);
		exec_close_fd(p[1]);
		pype->write = i;
	}
	else
		pype->write = p[1];

	/* dprintf(11, "### DEBUG %s\n", __func__); */
	/* dprintf(11, "read %d\n", pype->read); */
	/* dprintf(11, "write %d\n", pype->write); */
	return (OK_);
}

void	pipe_kill_pipe_sequence(void)
{
	error_print("execution: pipe");
	kill(0, SIGABRT);
}
