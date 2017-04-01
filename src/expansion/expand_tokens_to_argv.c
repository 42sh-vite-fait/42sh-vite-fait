/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens_to_argv.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:18:54 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:18:55 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "parser.h"
#include "expansion.h"
#include "array_42.h"
#include "memory_42.h"
#include "string_42.h"

t_array	expand_tokens_to_argv(t_array tokens, const t_string *input)
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
		word = expand_quote_removal(input->str + token->start, token->len);
		array_push(&argv, &word);
		i += 1;
	}
	word = NULL;
	array_push(&argv, &word);
	argv.len -= 1;
	return (argv);
}
