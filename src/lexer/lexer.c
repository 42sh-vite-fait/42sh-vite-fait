#include "lexer.h"

static void	lexer_complete(t_lexer *self)
{
	self->input_current_index = 0;
	self->token_begin_index = 0;
}

int		lexer_lex(t_lexer *self, t_array *tokens, const char *input)
{
	int		lexing_status;

	lexing_status = lexer_tokenize(self, tokens, input);
	if (lexing_status == LEXER_ERROR)
		return (LEXER_ERROR);
	categorize_tokens(tokens, input);
	lexer_clear_tokens(tokens);
	if (lexing_status == LEXER_INPUT_COMPLETE)
		lexer_complete(self);
	return (lexing_status);
}
