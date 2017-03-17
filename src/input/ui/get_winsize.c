#include "terminal.h"
/*
 * TODO
 * Le fd d'ecriture doit être stdin pour garantir qu'il s'agit d'un terminal
 */

int			get_cols(void)
{
	struct winsize		ts;
	int	ret;

	ret = ioctl(1, TIOCGWINSZ, &ts);
	assert(ret != -1);
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
