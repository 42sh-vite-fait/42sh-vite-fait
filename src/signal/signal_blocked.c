#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>
#include "macros_42.h"
#include "sig.h"

extern const int	g_exit_signals[];
extern const size_t	g_exit_signals_len;

static sigset_t	get_exit_sigset(void)
{
	sigset_t	exit_set;
	size_t		i;

	sigemptyset(&exit_set);
	i = 0;
	while (i < g_exit_signals_len)
	{
		sigaddset(&exit_set, g_exit_signals[i]);
		i += 1;
	}
	return (exit_set);
}

void			signal_unblock_exit_signals(void)
{
	sigset_t	blocked;
	int			ret;

	blocked = get_exit_sigset();
	ret = sigprocmask(SIG_UNBLOCK, &blocked, NULL);
	assert(ret == 0);
	(void)ret;
}

void			signal_block_exit_signals(void)
{
	sigset_t	blocked;
	int			ret;

	blocked = get_exit_sigset();
	ret = sigprocmask(SIG_BLOCK, &blocked, NULL);
	assert(ret == 0);
	(void)ret;
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

bool			signal_should_we_restart_the_loop(void)
{
	sigset_t	pending;
	size_t		i;

	i = 0;
	sigpending(&pending);
	while (i < g_exit_signals_len)
	{
		if (sigismember(&pending, g_exit_signals[i]))
		{
			signal_unblock_exit_signals();
			signal_block_exit_signals();
			return (true);
		}
		i += 1;
	}
	return (false);
}
