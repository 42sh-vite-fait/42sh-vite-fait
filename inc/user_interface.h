#ifndef USER_INTERFACE_H
# define USER_INTERFACE_H

# include <sys/ioctl.h>
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
# include <term.h>
# include <stdbool.h>
# include <stdint.h>
# include "lib42.h"
# include "history.h"

# define UI_COLOR_CYAN "\x1b[37m"
# define UI_COLOR_RESET "\x1b[36m"

# define MEM_PAGE_SIZE 4096

typedef struct s_cursor_pos		t_cursor_pos;
typedef struct s_editenv	t_editenv;
typedef struct s_key_mod	t_key_mod;

struct	s_key_action
{
	char	code[8];
	void	(*behavior_nomod)(t_editenv *);
	void	(*behavior_mod)(t_editenv *);
};

struct	s_cursor_pos
{
	size_t		x;
	size_t		y;
};

struct	s_editenv
{
	t_cursor_pos	cpos;
	t_string		entry;
	t_string		rbuff;
	t_string		cpy;
	t_string		initial_entry;
	const char		*prompt;
	size_t			last_entry_len;
	size_t			selection_size;
	size_t			selection_offset;
	size_t			rbuff_index;
	size_t			entry_index;
	int				history_index;
	int				arg_num;
	bool			must_leave;
	bool			is_selecting;
	uint8_t			pad[2];
};

enum	e_keys
{
	E_CTRL_AT = 0,
	E_CTRL_A = 1,
	E_CTRL_B = 2,
	E_CTRL_C = 3,
	E_CTRL_D = 4,
	E_CTRL_E = 5,
	E_CTRL_F = 6,
	E_CTRL_G = '\a',
	E_CTRL_H = '\b',
	E_CTRL_I = '\t',
	E_CTRL_J = '\n',
	E_CTRL_K = '\v',
	E_CTRL_L = '\f',
	E_CTRL_M = '\r',
	E_CTRL_N = 14,
	E_CTRL_O = 15,
	E_CTRL_P = 16,
	E_CTRL_Q = 17,
	E_CTRL_R = 18,
	E_CTRL_S = 19,
	E_CTRL_T = 20,
	E_CTRL_U = 21,
	E_CTRL_V = 22,
	E_CTRL_W = 23,
	E_CTRL_X = 24,
	E_CTRL_Y = 25,
	E_CTRL_Z = 26,
	E_CTRL_LBRACKET = 27,
	E_CTRL_BACKSLASH = 28,
	E_CTRL_RBRACKET = 29,
	E_CTRL_CARET = 30,
	E_CTRL_UNDERLINE = 31,
	E_SPACE = ' ',
	E_EXCLMARK = '!',
	E_DBL_QUOTE = '"',
	E_HASH_SIGN = '#',
	E_DOLLAR_SIGN = '$',
	E_PERCENT_SIGN = '%',
	E_AMPERAND = '&',
	E_SGL_QUOTE = '\'',
	E_LEFT_PAREN = '(',
	E_RIGHT_PAREN = ')',
	E_ASTERISK = '*',
	E_PLUS = '+',
	E_COMMA = ',',
	E_MINUS = '-',
	E_DOT = '.',
	E_SLASH = '/',
	E_DIGIT_0 = '0',
	E_DIGIT_1 = '1',
	E_DIGIT_2 = '2',
	E_DIGIT_3 = '3',
	E_DIGIT_4 = '4',
	E_DIGIT_5 = '5',
	E_DIGIT_6 = '6',
	E_DIGIT_7 = '7',
	E_DIGIT_8 = '8',
	E_DIGIT_9 = '9',
	E_COLON = ':',
	E_SEMI_COLON = ';',
	E_LESS_THAN = '<',
	E_EQUAL = '=',
	E_GREATER_THAN = '>',
	E_QUESTION_MARK = '?',
	E_AT_SIGN = '@',
	E_UPPER_A = 'A',
	E_UPPER_B = 'B',
	E_UPPER_C = 'C',
	E_UPPER_D = 'D',
	E_UPPER_E = 'E',
	E_UPPER_F = 'F',
	E_UPPER_G = 'G',
	E_UPPER_H = 'H',
	E_UPPER_I = 'I',
	E_UPPER_J = 'J',
	E_UPPER_K = 'K',
	E_UPPER_L = 'L',
	E_UPPER_M = 'M',
	E_UPPER_N = 'N',
	E_UPPER_O = 'O',
	E_UPPER_P = 'P',
	E_UPPER_Q = 'Q',
	E_UPPER_R = 'R',
	E_UPPER_S = 'S',
	E_UPPER_T = 'T',
	E_UPPER_U = 'U',
	E_UPPER_V = 'V',
	E_UPPER_W = 'W',
	E_UPPER_X = 'X',
	E_UPPER_Y = 'Y',
	E_UPPER_Z = 'Z',
	E_LEFT_BRACKET = '[',
	E_BACKSLASH = '\\',
	E_RIGHT_BRACKET = ']',
	E_CIRCUMFLEX = '^',
	E_UNDERLINE = '_',
	E_BACKQUOTE = '`',
	E_LOWER_A = 'a',
	E_LOWER_B = 'b',
	E_LOWER_C = 'c',
	E_LOWER_D = 'd',
	E_LOWER_E = 'e',
	E_LOWER_F = 'f',
	E_LOWER_G = 'g',
	E_LOWER_H = 'h',
	E_LOWER_I = 'i',
	E_LOWER_J = 'j',
	E_LOWER_K = 'k',
	E_LOWER_L = 'l',
	E_LOWER_M = 'm',
	E_LOWER_N = 'n',
	E_LOWER_O = 'o',
	E_LOWER_P = 'p',
	E_LOWER_Q = 'q',
	E_LOWER_R = 'r',
	E_LOWER_S = 's',
	E_LOWER_T = 't',
	E_LOWER_U = 'u',
	E_LOWER_V = 'v',
	E_LOWER_W = 'w',
	E_LOWER_X = 'x',
	E_LOWER_Y = 'y',
	E_LOWER_Z = 'z',
	E_LEFT_BRACE = '{',
	E_PIPE = '|',
	E_RIGHT_BRACE = '}',
	E_TILDE = '~',
	E_BACKSPACE = 127,
	E_ARROW_UP,
	E_ARROW_DOWN,
	E_ARROW_RIGHT,
	E_ARROW_LEFT,
	E_SHIFT_TAB,
	E_HOME,
	E_INSERT,
	E_DELETE,
	E_END,
	E_PAGE_UP,
	E_PAGE_DOWN,
	E_CTRL_ARROW_UP,
	E_CTRL_ARROW_DOWN,
	E_CTRL_ARROW_RIGHT,
	E_CTRL_ARROW_LEFT,
	E_MAX_ASCII_CHAR,
	E_START_ESC_SEQ = E_ARROW_UP,
	E_ESC = E_CTRL_LBRACKET,
	E_TAB = E_CTRL_I,
	E_ENTER = E_CTRL_M,
};

/*
** prompt interface
*/
size_t 		prompt(const char *prompt);
/*
** UI main interface
*/
int			ui_get_user_input(t_string *input, const char *prompt);

/*
**			UI workflow
*/
void		ui_display_user_entry(t_editenv *e);
void		read_user_entry(t_editenv *e);
int			stop_termcap(void);
int			start_termcap(void);
void 		ui_execute_handler(t_editenv *e);
void		ui_minimalist_display_user_entry(t_editenv *e);

/*
** termcap command
*/
void		term_command(char *entry);
void		term_newline(void);
void		term_clear_bottom(void);
void		term_restore_cursor(void);
void		term_toggle_video_mode(void);
void		term_save_cursor(void);
void		term_delete(int len);
void		term_move_cursor_row(int n);
int			get_cols(void);
int			get_lines(void);
int			tputs_write(int c);
void		term_mode(void);
void		normal_mode(void);

/*
** handler
*/
void		ui_leave(t_editenv *e);
void 		ui_clear(t_editenv *e);
void 		ui_display_word_expansion(t_editenv *e);
void 		ui_sharp(t_editenv *e);
void 		ui_arg_num(t_editenv *e);
void 		ui_change_case(t_editenv *e);
void 		ui_move_to_first_non_blank(t_editenv *e);
void		ui_move_position_count_right(t_editenv *e);
void 		ui_move_position_count_left(t_editenv *e);

// Edition
void		ui_handler_do_nothing(t_editenv *env);
void		ui_handler_insert_char(t_editenv *env);
void		ui_handler_valid_line(t_editenv *e);

// Left deletion
void		ui_handler_delete_left_char(t_editenv *e);
void		ui_handler_delete_left_word(t_editenv *e);
void		ui_handler_delete_left_begin(t_editenv *e);

// Right deletion
void		ui_handler_delete_right_char(t_editenv *e);
void		ui_handler_delete_right_word(t_editenv *e);
void		ui_handler_delete_right_end(t_editenv *e);

// Left motion
void		ui_handler_move_left_word(t_editenv *e);
void		ui_handler_move_left_char(t_editenv *e);
void		ui_handler_move_home(t_editenv *e);

// Right motion
void		ui_handler_move_right_word(t_editenv *e);
void		ui_handler_move_right_char(t_editenv *e);
void		ui_handler_move_end(t_editenv *e);

// Up/Down motion
void		ui_handler_move_down(t_editenv *e);
void		ui_handler_move_up(t_editenv *e);

// Clipboard
void		ui_handler_copy(t_editenv *e);
void		ui_handler_cut(t_editenv *e);
void		ui_handler_paste(t_editenv *e);
void		ui_handler_visual_selection(t_editenv *e);

// History
void		ui_handler_up_history(t_editenv *e);
void		ui_handler_down_history(t_editenv *e);

#endif
