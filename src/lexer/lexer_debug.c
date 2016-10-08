#include "lexer.h"
#include "ft_printf.h"
#include "array_42.h"

static char	*g_token_str[] = {
	[E_TOKEN_WORD] = "WORD",
	[E_TOKEN_PIPE] = "PIPE",
	[E_TOKEN_SEMICOLON] = "SEMICOLON",
	[E_TOKEN_LESS] = "LESS",
	[E_TOKEN_DLESS] = "DLESS",
	[E_TOKEN_LESSAND] = "LESSAND",
	[E_TOKEN_GREAT] = "GREAT",
	[E_TOKEN_DGREAT] = "DGREAT",
	[E_TOKEN_GREATAND] = "GREATAND",
	[E_TOKEN_NEWLINE] = "NEWLINE",
	[E_TOKEN_LESSGREAT] = "LESSGREAT",
	[E_TOKEN_DLESSDASH] = "DLESSDASH",
	[E_TOKEN_CLOBBER] = "CLOBBER",
	[E_TOKEN_AND] = "AND",
	[E_TOKEN_AND_IF] = "AND_IF",
	[E_TOKEN_DSEMI] = "DSEMI",
	[E_TOKEN_OR_IF] = "OR_IF",
	[E_TOKEN_LPAREN] = "LPAREN",
	[E_TOKEN_RPAREN] = "RPAREN",
	[E_TOKEN_COMMENT] = "COMMENT",
	[E_TOKEN_BLANK] = "BLANK",
};

void	lexer_debug_print_tokens(const t_array *tokens, const char *line)
{
	t_token		*token;
	char		*str;
	size_t		i;

	i = 0;
	ft_printf("TOKENS:\n");
	while (i < tokens->len)
	{
		token = (t_token *)array_get_at(tokens, i);
		str = ft_strsub(line, token->start, token->len);
		ft_printf("%s (start: %zu, len: %zu)\t%s \n",
				g_token_str[token->type],
				token->start,
				token->len,
				str);
		free(str);
		i += 1;
	}
}
