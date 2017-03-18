#ifndef TERMINAL_H
# define TERMINAL_H

# define CAPS_CURSOR_UP		"up"
# define CAPS_CURSOR_DOWN	"do"
# define CAPS_CURSOR_LEFT	"le"
# define CAPS_CURSOR_RIGHT	"nd"
# define CAPS_CLEAR_EOL		"ce"
# define CAPS_CLEAR_EOS		"cd"

int				init_terminal_module(void);
int				terminal_start_raw_mode(void);
int				terminal_stop_raw_mode(void);
struct winsize	terminal_get_winsize(void);
unsigned		terminal_get_rows(void);
unsigned		terminal_get_cols(void);
void			terminal_move_cursor(const char *cap, unsigned len);
void			terminal_execute_caps(const char *cap);
int				terminal_check_caps(void);

#endif
