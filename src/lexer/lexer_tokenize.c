#include "lexer.h"

/*
** Char -> Symbol Table
*/
static const uint8_t	g_char_to_symbol[CHAR_MAX + 1] = {
	[0] = E_SYMBOL_LETTER,
	[1] = E_SYMBOL_LETTER,
	[2] = E_SYMBOL_LETTER,
	[3] = E_SYMBOL_LETTER,
	[4] = E_SYMBOL_LETTER,
	[5] = E_SYMBOL_LETTER,
	[6] = E_SYMBOL_LETTER,
	[7] = E_SYMBOL_LETTER,
	[8] = E_SYMBOL_LETTER,
	['\t'] = E_SYMBOL_BLANK,
	['\n'] = E_SYMBOL_NEWLINE,
	[11] = E_SYMBOL_LETTER,
	[12] = E_SYMBOL_LETTER,
	[13] = E_SYMBOL_LETTER,
	[14] = E_SYMBOL_LETTER,
	[15] = E_SYMBOL_LETTER,
	[16] = E_SYMBOL_LETTER,
	[17] = E_SYMBOL_LETTER,
	[18] = E_SYMBOL_LETTER,
	[19] = E_SYMBOL_LETTER,
	[20] = E_SYMBOL_LETTER,
	[21] = E_SYMBOL_LETTER,
	[22] = E_SYMBOL_LETTER,
	[23] = E_SYMBOL_LETTER,
	[24] = E_SYMBOL_LETTER,
	[25] = E_SYMBOL_LETTER,
	[26] = E_SYMBOL_LETTER,
	[27] = E_SYMBOL_LETTER,
	[28] = E_SYMBOL_LETTER,
	[29] = E_SYMBOL_LETTER,
	[30] = E_SYMBOL_LETTER,
	[31] = E_SYMBOL_LETTER,
	[' '] = E_SYMBOL_BLANK,
	['!'] = E_SYMBOL_LETTER,
	['"'] = E_SYMBOL_DQUOTE,
	['#'] = E_SYMBOL_HASH,
	['$'] = E_SYMBOL_DOLLAR,
	['%'] = E_SYMBOL_LETTER,
	['&'] = E_SYMBOL_AND,
	['\''] = E_SYMBOL_SQUOTE,
	['('] = E_SYMBOL_LPAREN,
	[')'] = E_SYMBOL_RPAREN,
	['*'] = E_SYMBOL_LETTER,
	['+'] = E_SYMBOL_LETTER,
	[','] = E_SYMBOL_LETTER,
	['-'] = E_SYMBOL_DASH,
	['.'] = E_SYMBOL_LETTER,
	['/'] = E_SYMBOL_LETTER,
	['0'] = E_SYMBOL_LETTER,
	['1'] = E_SYMBOL_LETTER,
	['2'] = E_SYMBOL_LETTER,
	['3'] = E_SYMBOL_LETTER,
	['4'] = E_SYMBOL_LETTER,
	['5'] = E_SYMBOL_LETTER,
	['6'] = E_SYMBOL_LETTER,
	['7'] = E_SYMBOL_LETTER,
	['8'] = E_SYMBOL_LETTER,
	['9'] = E_SYMBOL_LETTER,
	[':'] = E_SYMBOL_LETTER,
	[';'] = E_SYMBOL_SEMI,
	['<'] = E_SYMBOL_LESS,
	['='] = E_SYMBOL_LETTER,
	['>'] = E_SYMBOL_GREAT,
	['?'] = E_SYMBOL_LETTER,
	['@'] = E_SYMBOL_LETTER,
	['A'] = E_SYMBOL_LETTER,
	['B'] = E_SYMBOL_LETTER,
	['C'] = E_SYMBOL_LETTER,
	['D'] = E_SYMBOL_LETTER,
	['E'] = E_SYMBOL_LETTER,
	['F'] = E_SYMBOL_LETTER,
	['G'] = E_SYMBOL_LETTER,
	['H'] = E_SYMBOL_LETTER,
	['I'] = E_SYMBOL_LETTER,
	['J'] = E_SYMBOL_LETTER,
	['K'] = E_SYMBOL_LETTER,
	['L'] = E_SYMBOL_LETTER,
	['M'] = E_SYMBOL_LETTER,
	['N'] = E_SYMBOL_LETTER,
	['O'] = E_SYMBOL_LETTER,
	['P'] = E_SYMBOL_LETTER,
	['Q'] = E_SYMBOL_LETTER,
	['R'] = E_SYMBOL_LETTER,
	['S'] = E_SYMBOL_LETTER,
	['T'] = E_SYMBOL_LETTER,
	['U'] = E_SYMBOL_LETTER,
	['V'] = E_SYMBOL_LETTER,
	['W'] = E_SYMBOL_LETTER,
	['X'] = E_SYMBOL_LETTER,
	['Y'] = E_SYMBOL_LETTER,
	['Z'] = E_SYMBOL_LETTER,
	['['] = E_SYMBOL_LETTER,
	['\\'] = E_SYMBOL_BSLASH,
	[']'] = E_SYMBOL_LETTER,
	['^'] = E_SYMBOL_LETTER,
	['_'] = E_SYMBOL_LETTER,
	['`'] = E_SYMBOL_BQUOTE,
	['a'] = E_SYMBOL_LETTER,
	['b'] = E_SYMBOL_LETTER,
	['c'] = E_SYMBOL_LETTER,
	['d'] = E_SYMBOL_LETTER,
	['e'] = E_SYMBOL_LETTER,
	['f'] = E_SYMBOL_LETTER,
	['g'] = E_SYMBOL_LETTER,
	['h'] = E_SYMBOL_LETTER,
	['i'] = E_SYMBOL_LETTER,
	['j'] = E_SYMBOL_LETTER,
	['k'] = E_SYMBOL_LETTER,
	['l'] = E_SYMBOL_LETTER,
	['m'] = E_SYMBOL_LETTER,
	['n'] = E_SYMBOL_LETTER,
	['o'] = E_SYMBOL_LETTER,
	['p'] = E_SYMBOL_LETTER,
	['q'] = E_SYMBOL_LETTER,
	['r'] = E_SYMBOL_LETTER,
	['s'] = E_SYMBOL_LETTER,
	['t'] = E_SYMBOL_LETTER,
	['u'] = E_SYMBOL_LETTER,
	['v'] = E_SYMBOL_LETTER,
	['w'] = E_SYMBOL_LETTER,
	['x'] = E_SYMBOL_LETTER,
	['y'] = E_SYMBOL_LETTER,
	['z'] = E_SYMBOL_LETTER,
	['{'] = E_SYMBOL_LBRACE,
	['|'] = E_SYMBOL_PIPE,
	['}'] = E_SYMBOL_RBRACE,
	['~'] = E_SYMBOL_LETTER,
	[127] = E_SYMBOL_LETTER,
};

static enum e_token_type		g_state_to_token_table[] = {
	[E_STATE_ERR] = 0,
	[E_STATE_START] = 0,
	[E_STATE_BLANK] = E_TOKEN_BLANK,
	[E_STATE_WORD] = E_TOKEN_WORD,
	[E_STATE_PIPE] = E_TOKEN_PIPE,
	[E_STATE_SEMI] = E_TOKEN_SEMI,
	[E_STATE_LESS] = E_TOKEN_LESS,
	[E_STATE_DLESS] = E_TOKEN_DLESS,
	[E_STATE_LESSAND] = E_TOKEN_LESSAND,
	[E_STATE_GREAT] = E_TOKEN_GREAT,
	[E_STATE_DGREAT] = E_TOKEN_DGREAT,
	[E_STATE_GREATAND] = E_TOKEN_GREATAND,
	[E_STATE_NEWLINE] = E_TOKEN_NEWLINE,
	[E_STATE_LESSGREAT] = E_TOKEN_LESSGREAT,
	[E_STATE_DLESSDASH] = E_TOKEN_DLESSDASH,
	[E_STATE_CLOBBER] = E_TOKEN_CLOBBER,
	[E_STATE_AND] = E_TOKEN_AND,
	[E_STATE_AND_IF] = E_TOKEN_AND_IF,
	[E_STATE_DSEMI] = E_TOKEN_DSEMI,
	[E_STATE_OR_IF] = E_TOKEN_OR_IF,
	[E_STATE_LPAREN] = E_TOKEN_LPAREN,
	[E_STATE_RPAREN] = E_TOKEN_RPAREN,
	[E_STATE_BSLASH] = E_TOKEN_WORD,
	[E_STATE_DOLLAR] = E_TOKEN_WORD,
	[E_STATE_COMMENT] = E_TOKEN_COMMENT,
};

#define ERROR 1
#define SUCCESS 0

static int	lexer_tokenize_one(t_lexer *self, t_token *token,
								const char **input)
{
	t_symbol	symbol;

	while (**input)
	{
		if (**input < 0)
			return (ERROR);
		symbol = g_char_to_symbol[(int)**input];
		if (is_automaton_next_state_error(&self->tokenizer, symbol))
			break ;
		automaton_step(&self->tokenizer, symbol);
		self->input_current_index += 1;
		*input += 1;
	}
	if (self->tokenizer.current_state == START_STATE)
		return (ERROR);
	*token = (t_token){
		.start = self->token_begin_index,
		.len = (self->input_current_index - self->token_begin_index),
		.type = g_state_to_token_table[self->tokenizer.current_state]
	};
	return (SUCCESS);
}

int			lexer_tokenize(t_lexer *self, t_array *tokens, const char *input)
{
	t_token		tok;

	while (*input)
	{
		if (lexer_tokenize_one(self, &tok, &input) == ERROR)
			return (LEXER_ERROR);
		if (ARRAY_IS_EMPTY(&self->tokenizer.state_stack))
		{
			automaton_reset(&self->tokenizer);
			array_push(tokens, &tok);
			self->token_begin_index = self->input_current_index;
		}
	}
	if (ARRAY_IS_EMPTY(&self->tokenizer.state_stack))
		return (LEXER_INPUT_COMPLETE);
	return (LEXER_INPUT_INCOMPLETE);
}
