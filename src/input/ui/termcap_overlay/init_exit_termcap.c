#include "user_interface.h"

int		stop_termcap(void)
{
	struct termios term;

	term_command("ve");
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(0, 0, &term) == -1)
		return (-1);
	return (1);
}

int		start_termcap(void)
{
	char				*name_term;
	struct termios		term;


	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == -1)
		return (-1);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~(unsigned long)(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	return (1);
}

void	normal_mode(void)
{
	stop_termcap();
}

void	term_mode(void)
{
	if (start_termcap() < 0)
		exit(0);
	term_command("vi");
	term_command("bw");
}
