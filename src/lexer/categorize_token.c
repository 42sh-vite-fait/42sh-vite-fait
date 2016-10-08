#include "lexer.h"

void	categorize_tokens(t_array *tokens, const char *input)
{
	categorize_io_number(tokens, input);
}
