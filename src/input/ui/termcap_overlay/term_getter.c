#include "user_interface.h"

int			get_cols(void)
{
	struct winsize		ts;

	ioctl(1, TIOCGWINSZ, &ts);
	if (ts.ws_col <= 0)
		return (10);
	return (ts.ws_col);
}

int			get_lines(void)
{
	struct winsize		ts;

	ioctl(1, TIOCGWINSZ, &ts);
	if (ts.ws_row <= 0)
		return (10);
	return (ts.ws_row);
}
