/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_io_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:36:32 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:36:33 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <unistd.h>
#include "parser.h"
#include "stdlib_42.h"

#define CHAR_TO_DIGIT(c) ((c) - '0')

bool			check_requirements_io_redirect(const t_parser *parser)
{
	if (parser_check_current_token_type(parser, E_TOKEN_IO_NUMBER)
			|| check_requirements_io_here(parser)
			|| check_requirements_io_file(parser))
		return (true);
	return (false);
}

static size_t	get_default_io_number(int operator_type)
{
	if (operator_type == E_TOKEN_LESS
			|| operator_type == E_TOKEN_DLESS
			|| operator_type == E_TOKEN_LESSAND
			|| operator_type == E_TOKEN_LESSGREAT)
		return (STDIN_FILENO);
	else
		return (STDOUT_FILENO);
}

static size_t	parse_io_number(t_parser *parser)
{
	const t_token	*token;
	size_t			io_number;

	if (parser_check_current_token_type(parser, E_TOKEN_IO_NUMBER))
	{
		token = parser_get_current_token(parser);
		assert(token->len == 1);
		io_number = CHAR_TO_DIGIT(parser->input->str[token->start]);
		parser_consume_token(parser);
	}
	else
		io_number = get_default_io_number(
				parser_get_current_token(parser)->type);
	return (io_number);
}

/*
** io_redirect :           io_file
**             | IO_NUMBER io_file
**			   |           io_here
**			   | IO_NUMBER io_here
*/

int				predict_io_redirect(t_parser *parser,
		struct s_redirection *redir)
{
	int	ret;

	redir->io_number = parse_io_number(parser);
	redir->operator = parser_get_current_token(parser)->type;
	redir->word = parser_get_lookahead_token(parser, 1);
	if (check_requirements_io_file(parser))
		ret = predict_io_file(parser);
	else if (check_requirements_io_here(parser))
		ret = predict_io_here(parser, redir);
	else
		ret = ERROR_;
	return (ret);
}
