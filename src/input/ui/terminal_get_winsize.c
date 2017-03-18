#include <assert.h>
#include <unistd.h>
#include <sys/ioctl.h>

static struct winsize	g_winsize;

/*
 * TODO
 * Le fd d'ecriture doit être un fd lié avec un terminal
 */

struct winsize	terminal_get_winsize(void)
{
	int	ret;

	ret = ioctl(STDOUT_FILENO, TIOCGWINSZ, &g_winsize);
	assert(ret != -1);
	return (g_winsize);
}

unsigned		terminal_get_rows(void)
{
	return (g_winsize.ws_row);
}

unsigned		terminal_get_cols(void)
{
	return (g_winsize.ws_col);
}
