#include <assert.h>
#include <stdlib.h>
#include "macros_42.h"
#include "sig.h"

static int	g_signals_to_ignore[] = {
	SIGTTIN,
	SIGTTOU,
	SIGTSTP,
};

void	signal_set_ignored_signals_to_ignore(void)
{
	size_t	size;

	size = ARR_SIZ_MAX(g_signals_to_ignore);
	signal_set_signals_handler_for(g_signals_to_ignore, size, SIG_IGN);
}

void 	signal_set_ignored_signals_to_default(void)
{
	size_t	size;

	size = ARR_SIZ_MAX(g_signals_to_ignore);
	signal_set_signals_handler_for(g_signals_to_ignore, size, SIG_DFL);
}

/*
** Must be call only if the shell is in interactive mode
*/

void	init_signal_module(void)
{
	signal_set_ignored_signals_to_ignore();
	signal_set_blocked_signals();
}

void	signal_set_signals_handler_for(int sigs[], size_t size, t_sig handler)
{
	struct sigaction	act;
	size_t				i;
	int					ret;

	act.sa_handler = handler;
	i = 0;
	while (i < size)
	{
		ret = sigaction(sigs[i], &act, NULL);
		assert(ret == 0);
		i += 1;
	}
	(void)ret;
}
