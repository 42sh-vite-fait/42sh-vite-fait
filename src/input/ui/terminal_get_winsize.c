#include <assert.h>
#include <unistd.h>
#include <sys/ioctl.h>

/*
 * TODO
 * Le fd d'ecriture doit être un fd lié avec un terminal
 */

struct winsize	terminal_get_winsize(void)
{
	struct winsize	wsize;
	int				ret;

	ret = ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);
	assert(ret != -1);
	return (wsize);
}
