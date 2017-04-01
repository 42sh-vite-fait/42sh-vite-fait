/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:19:58 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:20:01 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user_interface.h"

static struct s_key_action	g_key_action_list[] = {
	[E_CTRL_AT] = {
		.code =	"\x00",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_A] = {
		.code =	"\x01",
		.behavior = &ui_handler_jump_start,
	},
	[E_CTRL_B] = {
		.code =	"\x02",
		.behavior = &ui_handler_jump_prev_word,
	},
	[E_CTRL_C] = {
		.code =	"\x03",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_D] = {
		.code =	"\x04",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_E] = {
		.code =	"\x05",
		.behavior = &ui_handler_jump_end,
	},
	[E_CTRL_F] = {
		.code =	"\x06",
		.behavior = &ui_handler_jump_next_word,
	},
	[E_CTRL_G] = {
		.code =	"\a",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_H] = {
		.code =	"\b",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_I] = {
		.code =	"\t",
		.behavior = &ui_handler_autocomplete,
	},
	[E_CTRL_J] = {
		.code =	"\n",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_K] = {
		.code =	"\v",
		.behavior = &ui_handler_kill_right,
	},
	[E_CTRL_L] = {
		.code =	"\f",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_M] = {
		.code =	"\r",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_N] = {
		.code =	"\x0e",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_O] = {
		.code =	"\x0f",
		.behavior = &ui_handler_kill_left_word,
	},
	[E_CTRL_P] = {
		.code =	"\x10",
		.behavior = &ui_handler_kill_right_word,
	},
	[E_CTRL_Q] = {
		.code =	"\x11",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_R] = {
		.code =	"\x12",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_S] = {
		.code =	"\x13",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_T] = {
		.code =	"\x14",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_U] = {
		.code =	"\x15",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_V] = {
		.code =	"\x16",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_W] = {
		.code =	"\x17",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_X] = {
		.code =	"\x18",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_Y] = {
		.code =	"\x19",
		.behavior = &ui_handler_yank,
	},
	[E_CTRL_Z] = {
		.code =	"\x1a",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_LBRACKET] = {
		.code =	"\x1b",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_BACKSLASH] = {
		.code =	"\x1c",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_RBRACKET] = {
		.code =	"\x1d",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_CARET] = {
		.code =	"\x1e",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_UNDERLINE] = {
		.code =	"\x1f",
		.behavior = &ui_handler_do_nothing,
	},
	[E_SPACE] = {
		.code =	" ",
		.behavior = &ui_handler_insert_char,
	},
	[E_EXCLMARK] = {
		.code =	"!",
		.behavior = &ui_handler_insert_char,
	},
	[E_DBL_QUOTE] = {
		.code =	"\"",
		.behavior = &ui_handler_insert_char,
	},
	[E_HASH_SIGN] = {
		.code =	"#",
		.behavior = &ui_handler_insert_char,
	},
	[E_DOLLAR_SIGN] = {
		.code =	"$",
		.behavior = &ui_handler_insert_char,
	},
	[E_PERCENT_SIGN] = {
		.code =	"%",
		.behavior = &ui_handler_insert_char,
	},
	[E_AMPERAND] = {
		.code =	"&",
		.behavior = &ui_handler_insert_char,
	},
	[E_SGL_QUOTE] = {
		.code =	"\'",
		.behavior = &ui_handler_insert_char,
	},
	[E_LEFT_PAREN] = {
		.code =	"(",
		.behavior = &ui_handler_insert_char,
	},
	[E_RIGHT_PAREN] = {
		.code =	")",
		.behavior = &ui_handler_insert_char,
	},
	[E_ASTERISK] = {
		.code =	"*",
		.behavior = &ui_handler_insert_char,
	},
	[E_PLUS] = {
		.code =	"+",
		.behavior = &ui_handler_insert_char,
	},
	[E_COMMA] = {
		.code =	",",
		.behavior = &ui_handler_insert_char,
	},
	[E_MINUS] = {
		.code =	"-",
		.behavior = &ui_handler_insert_char,
	},
	[E_DOT] = {
		.code =	".",
		.behavior = &ui_handler_insert_char,
	},
	[E_SLASH] = {
		.code =	"/",
		.behavior = &ui_handler_insert_char,
	},
	[E_DIGIT_0] = {
		.code =	"0",
		.behavior = &ui_handler_insert_char,
	},
	[E_DIGIT_1] = {
		.code =	"1",
		.behavior = &ui_handler_insert_char,
	},
	[E_DIGIT_2] = {
		.code =	"2",
		.behavior = &ui_handler_insert_char,
	},
	[E_DIGIT_3] = {
		.code =	"3",
		.behavior = &ui_handler_insert_char,
	},
	[E_DIGIT_4] = {
		.code =	"4",
		.behavior = &ui_handler_insert_char,
	},
	[E_DIGIT_5] = {
		.code =	"5",
		.behavior = &ui_handler_insert_char,
	},
	[E_DIGIT_6] = {
		.code =	"6",
		.behavior = &ui_handler_insert_char,
	},
	[E_DIGIT_7] = {
		.code =	"7",
		.behavior = &ui_handler_insert_char,
	},
	[E_DIGIT_8] = {
		.code =	"8",
		.behavior = &ui_handler_insert_char,
	},
	[E_DIGIT_9] = {
		.code =	"9",
		.behavior = &ui_handler_insert_char,
	},
	[E_COLON] = {
		.code =	":",
		.behavior = &ui_handler_insert_char,
	},
	[E_SEMI_COLON] = {
		.code =	";",
		.behavior = &ui_handler_insert_char,
	},
	[E_LESS_THAN] = {
		.code =	"<",
		.behavior = &ui_handler_insert_char,
	},
	[E_EQUAL] = {
		.code =	"=",
		.behavior = &ui_handler_insert_char,
	},
	[E_GREATER_THAN] = {
		.code =	">",
		.behavior = &ui_handler_insert_char,
	},
	[E_QUESTION_MARK] = {
		.code =	"?",
		.behavior = &ui_handler_insert_char,
	},
	[E_AT_SIGN] = {
		.code =	"@",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_A] = {
		.code =	"A",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_B] = {
		.code =	"B",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_C] = {
		.code =	"C",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_D] = {
		.code =	"D",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_E] = {
		.code =	"E",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_F] = {
		.code =	"F",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_G] = {
		.code =	"G",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_H] = {
		.code =	"H",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_I] = {
		.code =	"I",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_J] = {
		.code =	"J",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_K] = {
		.code =	"K",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_L] = {
		.code =	"L",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_M] = {
		.code =	"M",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_N] = {
		.code =	"N",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_O] = {
		.code =	"O",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_P] = {
		.code =	"P",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_Q] = {
		.code =	"Q",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_R] = {
		.code =	"R",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_S] = {
		.code =	"S",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_T] = {
		.code =	"T",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_U] = {
		.code =	"U",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_V] = {
		.code =	"V",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_W] = {
		.code =	"W",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_X] = {
		.code =	"X",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_Y] = {
		.code =	"Y",
		.behavior = &ui_handler_insert_char,
	},
	[E_UPPER_Z] = {
		.code =	"Z",
		.behavior = &ui_handler_insert_char,
	},
	[E_LEFT_BRACKET] = {
		.code =	"[",
		.behavior = &ui_handler_insert_char,
	},
	[E_BACKSLASH] = {
		.code =	"\\",
		.behavior = &ui_handler_insert_char,
	},
	[E_RIGHT_BRACKET] = {
		.code =	"]",
		.behavior = &ui_handler_insert_char,
	},
	[E_CIRCUMFLEX] = {
		.code =	"^",
		.behavior = &ui_handler_insert_char,
	},
	[E_UNDERLINE] = {
		.code =	"_",
		.behavior = &ui_handler_insert_char,
	},
	[E_BACKQUOTE] = {
		.code =	"`",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_A] = {
		.code =	"a",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_B] = {
		.code =	"b",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_C] = {
		.code =	"c",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_D] = {
		.code =	"d",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_E] = {
		.code =	"e",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_F] = {
		.code =	"f",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_G] = {
		.code =	"g",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_H] = {
		.code =	"h",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_I] = {
		.code =	"i",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_J] = {
		.code =	"j",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_K] = {
		.code =	"k",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_L] = {
		.code =	"l",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_M] = {
		.code =	"m",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_N] = {
		.code =	"n",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_O] = {
		.code =	"o",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_P] = {
		.code =	"p",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_Q] = {
		.code =	"q",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_R] = {
		.code =	"r",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_S] = {
		.code =	"s",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_T] = {
		.code =	"t",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_U] = {
		.code =	"u",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_V] = {
		.code =	"v",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_W] = {
		.code =	"w",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_X] = {
		.code =	"x",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_Y] = {
		.code =	"y",
		.behavior = &ui_handler_insert_char,
	},
	[E_LOWER_Z] = {
		.code =	"z",
		.behavior = &ui_handler_insert_char,
	},
	[E_LEFT_BRACE] = {
		.code =	"{",
		.behavior = &ui_handler_insert_char,
	},
	[E_PIPE] = {
		.code =	"|",
		.behavior = &ui_handler_insert_char,
	},
	[E_RIGHT_BRACE] = {
		.code =	"}",
		.behavior = &ui_handler_insert_char,
	},
	[E_TILDE] = {
		.code =	"~",
		.behavior = &ui_handler_insert_char,
	},
	[E_BACKSPACE] = {
		.code =	"\x7f",
		.behavior = &ui_handler_delete_left,
	},
	[E_ARROW_UP] = {
		.code =	"[A",
		.behavior = &ui_handler_history_prev,
	},
	[E_ARROW_DOWN] = {
		.code =	"[B",
		.behavior = &ui_handler_history_next,
	},
	[E_ARROW_RIGHT] = {
		.code =	"[C",
		.behavior = &ui_handler_move_right,
	},
	[E_ARROW_LEFT] = {
		.code =	"[D",
		.behavior = &ui_handler_move_left,
	},
	[E_SHIFT_TAB] = {
		.code =	"[Z",
		.behavior = &ui_handler_do_nothing,
	},
	[E_HOME] = {
		.code =	"[H",
		.behavior = &ui_handler_do_nothing,
	},
	[E_INSERT] = {
		.code =	"[2~",
		.behavior = &ui_handler_do_nothing,
	},
	[E_DELETE] = {
		.code =	"[3~",
		.behavior = &ui_handler_delete_right,
	},
	[E_END] = {
		.code =	"[F",
		.behavior = &ui_handler_do_nothing,
	},
	[E_PAGE_UP] = {
		.code =	"[5~",
		.behavior = &ui_handler_move_up,
	},
	[E_PAGE_DOWN] = {
		.code =	"[6~",
		.behavior = &ui_handler_move_down,
	},
	[E_CTRL_ARROW_UP] = {
		.code =	"OA",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_ARROW_DOWN] = {
		.code =	"OB",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_ARROW_RIGHT] = {
		.code =	"OC",
		.behavior = &ui_handler_do_nothing,
	},
	[E_CTRL_ARROW_LEFT] = {
		.code =	"OD",
		.behavior = &ui_handler_do_nothing,
	},
};

static t_input_handler	*get_escape_sequence_handler(t_input_sequence *input)
{
	struct s_key_action	action;
	size_t				i;

	i = E_ARROW_UP;
	if (input->len == 1)
		return (NULL);
	while (i <= E_CTRL_ARROW_LEFT)
	{
		action = g_key_action_list[i];
		if (!ft_strncmp(action.code, input->data + 1, input->len - 1))
		{
			if (ft_strlen(action.code) == input->len - 1)
			{
				input->len = 0;
				return (action.behavior);
			}
			else
				return (NULL);
		}
		i += 1;
	}
	input->len = 0;
	return (NULL);
}

void					input_sequence_handle(t_input_sequence *input,
											t_term_env *env)
{
	t_input_handler	*action;

	action = NULL;
	if (input->data[0] == E_ESC)
		action = get_escape_sequence_handler(input);
	else if (input->data[0] >= 0)
	{
		action = g_key_action_list[(size_t)input->data[0]].behavior;
		input->len = 0;
	}
	else
		input->len = 0;
	if (action != NULL)
		action(env, input->data[0]);
}
