#include "ctype_42.h"
#include "lexer.h"

static bool	is_only_digit(const char *input, size_t len)
{
	size_t	index;

	index = 0;
	while (index < len)
	{
		if (!FT_ISDIGIT(input[index]))
			return (false);
		index += 1;
	}
	return (true);
}

static bool	is_token_redirection(int type)
{
	if (type == E_TOKEN_LESS
			|| type == E_TOKEN_DLESS
			|| type == E_TOKEN_LESSAND
			|| type == E_TOKEN_GREAT
			|| type == E_TOKEN_DGREAT
			|| type == E_TOKEN_GREATAND
			|| type == E_TOKEN_LESSGREAT
			|| type == E_TOKEN_DLESSDASH
			|| type == E_TOKEN_CLOBBER)
		return (true);
	return (false);
}

void	categorize_io_number(t_array *tokens, const char *input)
{
	t_token	*token;
	t_token	*prev;
	size_t	index;

	index = 0;
	while (index < tokens->len)
	{
		token = array_get_at(tokens, index);
		if (is_token_redirection(token->type) && index > 0)
		{
			prev = array_get_at(tokens, index - 1);
			if (prev->type == E_TOKEN_WORD
					&& is_only_digit(input + prev->start, prev->len))
				prev->type = E_TOKEN_IO_NUMBER;
		}
		index += 1;
	}
}
