#include <assert.h>
#include "parser.h"
#include "expansion.h"
#include "array_42.h"
#include "memory_42.h"
#include "string_42.h"

t_array	expand_tokens_to_argv(t_array tokens)
{
	t_array	argv;
	t_token	*token;
	char	*word;
	size_t	i;

	assert(tokens.len != 0);
	fatal_malloc(array_init_with_capacity(&argv, sizeof(char*),
				tokens.len + 1));
	i = 0;
	while (i < tokens.len)
	{
		token = *(t_token**)array_get_at(&tokens, i);
		word = expand_quote_removal(token->str, token->len);
		array_push(&argv, &word);
		i += 1;
	}
	word = NULL;
	array_push(&argv, &word);
	return (argv);
}
