#include "terminal.h"

void	term_command(char *entry)
{
	char *res;

	res = tgetstr(entry, NULL);
	if (res == NULL)
		return ;
	tputs(res, 0, tputs_write);
}

void	term_save_cursor(void)
{
	term_command("sc");
}

void	term_clear_bottom(void)
{
	term_command("cd");
}

void	term_restore_cursor(void)
{
	term_command("rc");
}

void	term_newline(void)
{
	term_command("nw");
}
