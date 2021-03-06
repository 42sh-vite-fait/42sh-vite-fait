/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_clear_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:21:34 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:21:36 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		lexer_clear_tokens(t_array *tokens)
{
	size_t		it;
	size_t		new_it;
	t_token		*token;

	it = 0;
	new_it = 0;
	while (it != tokens->len)
	{
		token = (t_token *)array_get_at(tokens, it);
		if (token->type != E_TOKEN_BLANK &&
			token->type != E_TOKEN_COMMENT)
		{
			array_set_at(tokens, new_it, token);
			new_it += 1;
		}
		it += 1;
	}
	array_truncate(tokens, new_it);
	return (0);
}
