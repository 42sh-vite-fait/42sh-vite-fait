#include "user_interface.h"

static void		ui_handler_do_nothing(void *a)
{
	(void)a;
}

static struct s_key_action	g_key_action_list[] = {
	[E_CTRL_AT] = {
		.code =	"\x00",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_A] = {
		.code =	"\x01",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_B] = {
		.code =	"\x02",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_C] = {
		.code =	"\x03",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_D] = {
		.code =	"\x04",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_E] = {
		.code =	"\x05",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_F] = {
		.code =	"\x06",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_G] = {
		.code =	"\a",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_H] = {
		.code =	"\b",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_I] = {
		.code =	"\t",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_J] = {
		.code =	"\n",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_K] = {
		.code =	"\v",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_L] = {
		.code =	"\f",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_M] = {
		.code =	"\r",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_N] = {
		.code =	"\x0e",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_O] = {
		.code =	"\x0f",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_P] = {
		.code =	"\x10",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_Q] = {
		.code =	"\x11",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_R] = {
		.code =	"\x12",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_S] = {
		.code =	"\x13",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_T] = {
		.code =	"\x14",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_U] = {
		.code =	"\x15",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_V] = {
		.code =	"\x16",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_W] = {
		.code =	"\x17",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_X] = {
		.code =	"\x18",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_Y] = {
		.code =	"\x19",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_Z] = {
		.code =	"\x1a",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_LBRACKET] = {
		.code =	"\x1b",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_BACKSLASH] = {
		.code =	"\x1c",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_RBRACKET] = {
		.code =	"\x1d",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_CARET] = {
		.code =	"\x1e",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_UNDERLINE] = {
		.code =	"\x1f",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_SPACE] = {
		.code =	" ",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_EXCLMARK] = {
		.code =	"!",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_DBL_QUOTE] = {
		.code =	"\"",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_HASH_SIGN] = {
		.code =	"#",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_DOLLAR_SIGN] = {
		.code =	"$",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_PERCENT_SIGN] = {
		.code =	"%",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_AMPERAND] = {
		.code =	"&",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_SGL_QUOTE] = {
		.code =	"\'",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LEFT_PAREN] = {
		.code =	"(",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_RIGHT_PAREN] = {
		.code =	")",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_ASTERISK] = {
		.code =	"*",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_PLUS] = {
		.code =	"+",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_COMMA] = {
		.code =	",",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_MINUS] = {
		.code =	"-",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_DOT] = {
		.code =	".",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_SLASH] = {
		.code =	"/",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_DIGIT_0] = {
		.code =	"0",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_DIGIT_1] = {
		.code =	"1",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_DIGIT_2] = {
		.code =	"2",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_DIGIT_3] = {
		.code =	"3",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_DIGIT_4] = {
		.code =	"4",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_DIGIT_5] = {
		.code =	"5",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_DIGIT_6] = {
		.code =	"6",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_DIGIT_7] = {
		.code =	"7",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_DIGIT_8] = {
		.code =	"8",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_DIGIT_9] = {
		.code =	"9",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_COLON] = {
		.code =	":",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_SEMI_COLON] = {
		.code =	";",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LESS_THAN] = {
		.code =	"<",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_EQUAL] = {
		.code =	"=",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_GREATER_THAN] = {
		.code =	">",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_QUESTION_MARK] = {
		.code =	"?",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_AT_SIGN] = {
		.code =	"@",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_A] = {
		.code =	"A",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_B] = {
		.code =	"B",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_C] = {
		.code =	"C",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_D] = {
		.code =	"D",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_E] = {
		.code =	"E",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_F] = {
		.code =	"F",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_G] = {
		.code =	"G",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_H] = {
		.code =	"H",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_I] = {
		.code =	"I",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_J] = {
		.code =	"J",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_K] = {
		.code =	"K",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_L] = {
		.code =	"L",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_M] = {
		.code =	"M",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_N] = {
		.code =	"N",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_O] = {
		.code =	"O",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_P] = {
		.code =	"P",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_Q] = {
		.code =	"Q",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_R] = {
		.code =	"R",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_S] = {
		.code =	"S",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_T] = {
		.code =	"T",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_U] = {
		.code =	"U",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_V] = {
		.code =	"V",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_W] = {
		.code =	"W",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_X] = {
		.code =	"X",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_Y] = {
		.code =	"Y",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UPPER_Z] = {
		.code =	"Z",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LEFT_BRACKET] = {
		.code =	"[",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_BACKSLASH] = {
		.code =	"\\",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_RIGHT_BRACKET] = {
		.code =	"]",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CIRCUMFLEX] = {
		.code =	"^",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_UNDERLINE] = {
		.code =	"_",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_BACKQUOTE] = {
		.code =	"`",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_A] = {
		.code =	"a",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_B] = {
		.code =	"b",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_C] = {
		.code =	"c",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_D] = {
		.code =	"d",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_E] = {
		.code =	"e",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_F] = {
		.code =	"f",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_G] = {
		.code =	"g",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_H] = {
		.code =	"h",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_I] = {
		.code =	"i",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_J] = {
		.code =	"j",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_K] = {
		.code =	"k",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_L] = {
		.code =	"l",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_M] = {
		.code =	"m",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_N] = {
		.code =	"n",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_O] = {
		.code =	"o",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_P] = {
		.code =	"p",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_Q] = {
		.code =	"q",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_R] = {
		.code =	"r",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_S] = {
		.code =	"s",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_T] = {
		.code =	"t",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_U] = {
		.code =	"u",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_V] = {
		.code =	"v",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_W] = {
		.code =	"w",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_X] = {
		.code =	"x",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_Y] = {
		.code =	"y",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LOWER_Z] = {
		.code =	"z",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_LEFT_BRACE] = {
		.code =	"{",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_PIPE] = {
		.code =	"|",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_RIGHT_BRACE] = {
		.code =	"}",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_TILDE] = {
		.code =	"~",
		.behavior_nomod = &ui_handler_insert_char,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_BACKSPACE] = {
		.code =	"\x7f",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_ARROW_UP] = {
		.code =	"[A",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_ARROW_DOWN] = {
		.code =	"[B",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_ARROW_RIGHT] = {
		.code =	"[C",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_ARROW_LEFT] = {
		.code =	"[D",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_SHIFT_TAB] = {
		.code =	"[Z",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_HOME] = {
		.code =	"[H",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_INSERT] = {
		.code =	"[2~",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_DELETE] = {
		.code =	"[3~",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_END] = {
		.code =	"[F",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_PAGE_UP] = {
		.code =	"[5~",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_PAGE_DOWN] = {
		.code =	"[6~",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_ARROW_UP] = {
		.code =	"OA",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_ARROW_DOWN] = {
		.code =	"OB",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_ARROW_RIGHT] = {
		.code =	"OC",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
	[E_CTRL_ARROW_LEFT] = {
		.code =	"OD",
		.behavior_nomod = &ui_handler_do_nothing,
		.behavior_mod = &ui_handler_do_nothing
	},
};

void				handle_input_sequence(t_input_sequence *input)
{
	size_t				i;
	struct s_key_action	action;

 	i = E_ARROW_UP;
	if (input->data[0] == E_ESC)
	{
		while (i <= E_CTRL_ARROW_LEFT)
		{
			action = g_key_action_list[i];
			if (!ft_strcmp(action.code, input->data) &&
				ft_strlen(action.code) == input->len)
				break;
			else
				input->len = 0;
		}
	}
	else if (input->data[0] >= 0)
		action = g_key_action_list[(size_t)input->data[0]];
	else
	{
		input->len = 0;
		return ;
	}
	input->len = 0;
	action.behavior_nomod(NULL) //TODO: send real parameters;
}

