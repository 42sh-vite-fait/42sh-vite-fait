#ifndef SIG_H
# define SIG_H

# include <signal.h>
# include <stdbool.h>

typedef void (*t_sig) (int);

void 	init_signal_module(void);
void	signal_set_signals_handler_for(int sigs[], size_t size, t_sig handler);
void 	signal_set_blocked_signals(void);
void	signal_unblock_blocked_signals(void);
bool	signal_should_we_drop_the_command(void);
void	signal_set_ignored_signals_to_ignore(void);
void 	signal_set_ignored_signals_to_default(void);

#endif
