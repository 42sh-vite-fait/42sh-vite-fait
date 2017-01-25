#include "parser.h"
#include "array_42.h"
#include "string_42.h"

static size_t	get_total_len(t_array tokens)
{
	t_token	*token;
	size_t	len;
	size_t	i;
	
	i = 0;
	len = 0;
	while (i < tokens.len)
	{
		token = array_get_at(&tokens, i);
		len += token->len + 1;
		i += 1;
	}
	return (len);
}

static void	fill_array_with_buf()
{
	char		*tmp;

	tmp = str.str + str.len;
	array_push(&strs, &tmp);
	token = array_get_at(&tokens, i);

	ft_memcpy(buf, token->str, token->len);
	ft_memcpy(buf, "\0", 1);
}

char	**convert_to_str(t_array tokens)
{
	t_array		strs;
	char		*buf;
	t_token		*token;
	size_t		i;

	fatal_malloc(array_init_with_capacity(&strs, sizeof(char*),
				tokens.len + 1));
	buf = fatal_malloc(malloc(get_total_len(tokens)));
	i = 0;
	while (i < tokens.len)
	{
		i += 1;
	}
	tmp = NULL;
	array_push(&strs, &tmp);
	return (strs.data);
}
