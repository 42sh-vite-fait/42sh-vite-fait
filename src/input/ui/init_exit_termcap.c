#include "terminal.h"

static struct termios	g_termios_backup;

static int	terminal_set_termios(const struct termios *new)
{
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, new) < 0)
	{
		error_set_context("tcsetattr: %s", strerror(errno));
		return (ERROR_);
	}
	return (OK_);
}

int terminal_start_raw_mode(void)
{
	struct termios	raw;

	raw = g_termios_backup;
	raw.c_iflag &= ~(unsigned)IXON;
	raw.c_lflag &= ~(unsigned)(ICANON | ECHO | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	if (terminal_set_termios(&raw) != OK_)
		return (ERROR_);
	term_command("vi");
	term_command("bw");
	return (OK_);
}

int terminal_stop_raw_mode(void)
{
	term_command("ve");
	if (terminal_set_termios(&g_termios_backup) != OK_)
		return (ERROR_);
	return (OK_);
}

int init_terminal_module(void)
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
	if (tcgetattr(STDIN_FILENO, &g_termios_backup) < 0)
	{
		error_set_context("tcgetattr: %s", strerror(errno));
		return (ERROR_);
	}
	return (OK_);
}
