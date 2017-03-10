# define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <signal.h>
#include "macros_42.h"
#include "sig.h"

extern const int	g_signals_to_ignore[];
extern const size_t	g_signals_to_ignore_len;

void	signal_set_ignored_signals(void)
{
	struct sigaction	act;

	act.sa_handler = SIG_IGN;
	signal_set_handler_for(g_signals_to_ignore, g_signals_to_ignore_len, &act);
}

void 	signal_unset_ignored_signals(void)
{
	struct sigaction	act;

	act.sa_handler = SIG_DFL;
	signal_set_handler_for(g_signals_to_ignore, g_signals_to_ignore_len, &act);
}
