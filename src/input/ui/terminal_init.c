#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <term.h>
#include <stdlib.h>
#include <termios.h>
#include "errors.h"
#include "terminal.h"
#include "exec.h"

static struct termios	g_termios_backup;

static int	terminal_set_termios(const struct termios *new)
{
	if (tcsetattr(exec_get_tty_fd(), TCSADRAIN, new) < 0)
	{
		error_set_context("tcsetattr: %s", strerror(errno));
		return (ERROR_);
	}
	return (OK_);
}

int			terminal_start_raw_mode(void)
{
	struct termios	raw;

	raw = g_termios_backup;
	raw.c_iflag &= ~(unsigned)IXON;
	raw.c_lflag &= ~(unsigned)(ICANON | ECHO | IEXTEN);
	raw.c_lflag |= ISIG;
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	if (terminal_set_termios(&raw) != OK_)
		return (ERROR_);
	return (OK_);
}

int			terminal_stop_raw_mode(void)
{
	if (terminal_set_termios(&g_termios_backup) != OK_)
		return (ERROR_);
	return (OK_);
}

/*
** Must be called only if the shell is in interactive mode
*/

int			init_terminal_module(void)
{
	char	*name_term;

	if ((name_term = getenv("TERM")) == NULL)
	{
		error_set_context("TERM variable is missing");
		return (ERROR_);
	}
	if (tgetent(NULL, name_term) < 1)
	{
		if (name_term[0] == '\0')
			name_term = "(empty)";
		error_set_context("tgetent: no such entry for %s", name_term);
		return (ERROR_);
	}
	if (tcgetattr(exec_get_tty_fd(), &g_termios_backup) < 0)
	{
		error_set_context("tcgetattr: %s", strerror(errno));
		return (ERROR_);
	}
	return (terminal_check_caps());
}
