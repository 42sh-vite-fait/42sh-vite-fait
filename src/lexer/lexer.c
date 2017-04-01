#include <assert.h>
#include "lexer.h"

static void	lexer_complete(t_lexer *self)
{
	self->input_current_index = 0;
	self->token_begin_index = 0;
}

void		lexer_clear(t_lexer *self)
{
	automaton_reset(&self->tokenizer);
	lexer_complete(self);
}

int			lexer_lex(t_lexer *self, t_array *tokens, const t_string *input)
{
	int		lexing_status;

	assert(self != NULL);
	assert(tokens != NULL);
	assert(input != NULL);
	lexing_status = lexer_tokenize(self, tokens, input);
	if (lexing_status == LEXER_ERROR)
		return (LEXER_ERROR);
	if (lexing_status == LEXER_INPUT_COMPLETE)
		lexer_complete(self);
	return (lexing_status);
}
