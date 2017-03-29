#include "lexer.h"
#include "ft_printf.h"
#include "array_42.h"
#include <stdio.h>

static const char	*g_token_str[] = {
	[E_TOKEN_WORD] = "WORD",
	[E_TOKEN_PIPE] = "PIPE",
	[E_TOKEN_SEMI] = "SEMI",
	[E_TOKEN_LESS] = "LESS",
	[E_TOKEN_DLESS] = "DLESS",
	[E_TOKEN_LESSAND] = "LESSAND",
	[E_TOKEN_GREAT] = "GREAT",
	[E_TOKEN_DGREAT] = "DGREAT",
	[E_TOKEN_GREATAND] = "GREATAND",
	[E_TOKEN_NEWLINE] = "NEWLINE",
	[E_TOKEN_LESSGREAT] = "LESSGREAT",
	[E_TOKEN_AND] = "AND",
	[E_TOKEN_AND_IF] = "AND_IF",
	[E_TOKEN_OR_IF] = "OR_IF",
	[E_TOKEN_LPAREN] = "LPAREN",
	[E_TOKEN_RPAREN] = "RPAREN",
	[E_TOKEN_COMMENT] = "COMMENT",
	[E_TOKEN_BLANK] = "BLANK",
	[E_TOKEN_IO_NUMBER] = "IO_NUMBER",
	[E_TOKEN_END_OF_INPUT] = "END_OF_INPUT",
};

void	lexer_debug_print_token(const t_string *input, const t_token *token)
{
	printf("%s (start: %zu, len: %zu) [%.*s]\n",
			g_token_str[token->type],
			token->start,
			token->len,
			(int)token->len,
			input->str + token->start);
}

void	lexer_debug_print_tokens(const t_string *input, const t_array *tokens)
{
	size_t		i;

	i = 0;
	ft_printf("TOKENS:\n");
	while (i < tokens->len)
	{
		lexer_debug_print_token(input, array_get_at(tokens, i));
		i += 1;
	}
}

const char	*lexer_debug_get_token_name(size_t i)
{
	if (i < ARR_SIZ_MAX(g_token_str))
		return (g_token_str[i]);
	return (NULL);
}
