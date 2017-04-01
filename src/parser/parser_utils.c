/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:36:32 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:36:33 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "parser.h"

const t_token	*parser_get_lookahead_token(const t_parser *parser, size_t n)
{
	static const t_token	end_of_input = {

	.start = 0,
	.len = 0,
	.type = E_TOKEN_END_OF_INPUT
	};
	if (parser->index + n >= parser->tokens->len)
		return (&end_of_input);
	else
		return (array_get_at(parser->tokens, parser->index + n));
}

const t_token	*parser_get_current_token(const t_parser *parser)
{
	return (parser->current_token);
}

void			parser_consume_token(t_parser *parser)
{
	parser->index += 1;
	parser->current_token = parser_get_lookahead_token(parser, 0);
}

bool			parser_check_current_token_type(const t_parser *parser,
		int type)
{
	assert(parser->current_token != NULL);
	return (parser->current_token->type == type);
}

int				parser_consume_if_match(t_parser *parser, int type)
{
	if (parser_check_current_token_type(parser, type))
	{
		parser_consume_token(parser);
		return (OK_);
	}
	return (ERROR_);
}
