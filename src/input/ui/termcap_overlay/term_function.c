#include "user_interface.h"

int			tputs_write(int c)
{
	write(0, &c, 1);
	return (0);
}

void		term_move_cursor_row(int n)
{
	char *res;

	res = tgetstr("cv", NULL);
	tputs(tgoto(res, 0, n), 1, tputs_write);
}

void		term_toggle_video_mode(void)
{
	static int toggle = 0;

	if (!toggle)
		term_command("mr");
	else
		term_command("me");
	toggle = !toggle;
}

void		term_delete(int len)
{
	char *res;

	res = tgetstr("ec", NULL);
	tputs(tgoto(res, len, 0), 1, tputs_write);
}
