/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorize_io_number.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:21:34 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:22:04 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype_42.h"
#include "lexer.h"

/*
** POSIX.1 2008
** 2.7 Redirection
** > Open files are represented by decimal numbers starting with zero.
** > The largest possible value is implementation-defined;
** > however, all implementations shall support at least 0 to 9,
** > inclusive, for use by the application.
*/

bool		is_only_one_digit(const char *input)
{
	return (FT_ISDIGIT(input[0]) && !FT_ISDIGIT(input[1]));
}

static bool	is_token_redirection(int type)
{
	if (type == E_TOKEN_LESS
			|| type == E_TOKEN_DLESS
			|| type == E_TOKEN_LESSAND
			|| type == E_TOKEN_GREAT
			|| type == E_TOKEN_DGREAT
			|| type == E_TOKEN_GREATAND
			|| type == E_TOKEN_LESSGREAT)
		return (true);
	return (false);
}

void		categorize_io_number(const t_string *input, t_array *tokens)
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
					&& is_only_one_digit(input->str + prev->start))
				prev->type = E_TOKEN_IO_NUMBER;
		}
		index += 1;
	}
}
