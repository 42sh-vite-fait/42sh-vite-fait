# define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdbool.h>
#include "macros_42.h"
#include "sig.h"

/* static volatile sig_atomic_t	g_signal_handler_flag = 0; */
extern const int				g_exit_signals[];
extern const size_t				g_exit_signals_len;

static void	signal_handler_mark_interruption(int sig)
{
	(void)sig;
	/* g_signal_handler_flag = 1; */
}

void		signal_mute_exit_signals(void)
{
	struct sigaction	act;
	sigset_t			emptyset;

	sigemptyset(&emptyset);
	act.sa_handler = &signal_handler_mark_interruption;
	act.sa_mask = emptyset;
	act.sa_flags = SIGACT_NO_FLAG;
	signal_set_handler_for(g_exit_signals, g_exit_signals_len, &act);
}

void		signal_unmute_exit_signals(void)
{
	struct sigaction	act;

	act.sa_handler = SIG_DFL;
	signal_set_handler_for(g_exit_signals, g_exit_signals_len, &act);
}
