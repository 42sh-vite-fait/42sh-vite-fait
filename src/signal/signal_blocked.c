#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "macros_42.h"
#include "sig.h"

static int	g_signals_to_block[] = {
	SIGINT,
	SIGQUIT,
	SIGTERM,
};

static sigset_t	get_blocked_sigset(void)
{
	sigset_t	blocked;

	sigemptyset(&blocked);
	sigaddset(&blocked, SIGINT);
	sigaddset(&blocked, SIGQUIT);
	sigaddset(&blocked, SIGTERM);
	return (blocked);
}

void			signal_unblock_blocked_signals(void)
{
	sigset_t	blocked;
	int			ret;

	blocked = get_blocked_sigset();
	ret = sigprocmask(SIG_UNBLOCK, &blocked, NULL);
	assert(ret == 0);
}

void 			signal_set_blocked_signals(void)
{
	sigset_t	blocked;
	int			ret;

	blocked = get_blocked_sigset();
	ret = sigprocmask(SIG_BLOCK, &blocked, NULL);
	assert(ret == 0);
}

/*
** How does it works ?
** If a blocked signal is received it will be in the pending state,
** waiting to be delivered to the process once the signal is unblocked.
** If a signal (INT, QUIT or TERM) is pending, then we set the handler
** for this signals to SIG_IGN (ignore).
** We do that because once the signal is unblocked,
** it is immediately delivered to the process and his handler is executed.
** After that we unblock the blocked signals.
** The signal is received, ignored, and we re-block the signals.
** Finally we set the default handler for the signals,
** because an ignored signal is discarded and not blocked.
*/

bool			signal_should_we_drop_the_command(void)
{
	sigset_t	pending;
	size_t		size;
	size_t		i;

	size = ARR_SIZ_MAX(g_signals_to_block);
	i = 0;
	sigpending(&pending);
	while (i < size)
	{
		if (sigismember(&pending, g_signals_to_block[i]))
		{
			signal_set_signals_handler_for(g_signals_to_block, size, SIG_IGN);
			signal_unblock_blocked_signals();
			signal_set_blocked_signals();
			signal_set_signals_handler_for(g_signals_to_block, size, SIG_DFL);
			return (true);
		}
		i += 1;
	}
	return (false);
}
