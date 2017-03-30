/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interface.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 17:00:15 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 17:29:02 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_INTERFACE_H
# define USER_INTERFACE_H

# include <stdint.h>
# include "string_42.h"

typedef struct s_input_sequence	t_input_sequence;
typedef struct s_term_line		t_term_line;
typedef struct s_term_env		t_term_env;
typedef void					(t_input_handler)(t_term_env *, char);

struct	s_key_action
{
	char			code[8];
	t_input_handler	*behavior;
};

struct	s_input_sequence
{
	char	data[8];
	uint8_t	len;
};

struct	s_term_line
{
	t_string	*str;
	uint64_t	string_index;
	uint16_t	cursor_x;
	uint16_t	term_x;
};

enum	e_autocomplete_state
{
	E_NO_AUTOCOMPLETE,
	E_LAST_CMD_WAS_AUTOCOMPLETE,
	E_LAST_CMD_REALLY_WAS_AUTOCOMPLETE,
};

struct	s_term_env
{
	t_string	kill_buffer;
	t_array		autocomplete_matches;
	t_term_line	line;
	size_t		history_index;
	uint32_t	prompt_size;
	uint16_t	autocomplete_index;
	uint8_t		autocomplete_state;
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
	E_MAX_ASCII_CHAR = 127,
	E_START_ESC_SEQ = E_ARROW_UP,
	E_ESC = E_CTRL_LBRACKET,
	E_TAB = E_CTRL_I,
	E_ENTER = E_CTRL_M,
};

/*
** Line edition utilities
*/
void	line_move_cursor(t_term_line *line, int move);
int		line_move_offset_y(t_term_line *line, int move);
int		line_move_offset_x(t_term_line *line, int move);

void	line_print(t_term_line *line);
void	line_insert(t_term_line *line, const char *s, size_t len);
void	line_replace(t_term_line *line, const char *new_str,
		size_t new_str_len);
void	line_remove_left(t_term_line *line, size_t removed_len);
void	line_remove_right(t_term_line *line, size_t removed_len);

size_t	line_next_word_size(t_term_line *line);
size_t	line_prev_word_size(t_term_line *line);

/*
** Input handling
*/
void	input_sequence_handle(t_input_sequence *input, t_term_env *env);

/*
** Handlers
*/
void	ui_handler_kill_left(t_term_env *env, char c);
void	ui_handler_kill_right(t_term_env *env, char c);
void	ui_handler_kill_left_word(t_term_env *env, char c);
void	ui_handler_kill_right_word(t_term_env *env, char c);
void	ui_handler_yank(t_term_env *env, char c);

void	ui_handler_jump_end(t_term_env *env, char c);
void	ui_handler_jump_start(t_term_env *env, char c);
void	ui_handler_jump_next_word(t_term_env *env, char c);
void	ui_handler_jump_prev_word(t_term_env *env, char c);

void	ui_handler_do_nothing(t_term_env *env, char c);
void	ui_handler_delete_left(t_term_env *env, char c);
void	ui_handler_delete_right(t_term_env *env, char c);
void	ui_handler_insert_char(t_term_env *env, char c);

void	ui_handler_move_right(t_term_env *env, char c);
void	ui_handler_move_left(t_term_env *env, char c);
void	ui_handler_move_up(t_term_env *env, char c);
void	ui_handler_move_down(t_term_env *env, char c);

void	ui_handler_history_prev(t_term_env *env, char c);
void	ui_handler_history_next(t_term_env *env, char c);

void	ui_handler_autocomplete(t_term_env *env, char c);

/*
** Term environment utilities
*/
void	init_term_env(t_term_env *env, t_string *line, const char *prompt);
void	shutdown_term_env(t_term_env *env);
void	term_env_clear_autocompletion(t_term_env *env);

void	term_env_update_for_resize(t_term_env *env);

#endif
