#ifndef TERM_H
# define TERM_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>
# include "errors.h"
# include "memory_42.h"

/*
** Termios
*/
int 	init_terminal_module(void);
int 	terminal_start_raw_mode(void);
int 	terminal_stop_raw_mode(void);

/*
** Termcaps
*/
void	term_command(char *entry);
void	term_newline(void);
void	term_clear_bottom(void);
void	term_restore_cursor(void);
void	term_toggle_video_mode(void);
void	term_save_cursor(void);
void	term_delete(int len);
void	term_move_cursor_row(int n);
int		get_cols(void);
int		get_lines(void);
int		tputs_write(int c);

#endif
