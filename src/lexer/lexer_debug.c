/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:21:34 by djean             #+#    #+#             */
/*   Updated: 2017/04/02 12:43:13 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

const char	*lexer_debug_get_token_name(size_t i)
{
	if (i < ARR_SIZ_MAX(g_token_str))
		return (g_token_str[i]);
	return (NULL);
}
