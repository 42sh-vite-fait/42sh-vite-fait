#include "lexer.h"

void	categorize_tokens(const t_string *input, t_array *tokens)
{
	categorize_io_number(input, tokens);
}
