#include <ui.h>

int 		tputs_write(int c)
{
	write(0, &c, 1);
	return (0);
}

void        term_command(char *entry)
{
	char *res;

	res = tgetstr(entry, NULL);
	tputs(res, 0, tputs_write);
}

t_cursor 	term_get_cursor()
{

}

void		term_newine()
{
	term_command("nw");
}

void 		term_move_cursor(int x, int y)
{

}
