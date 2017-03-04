#include <stdlib.h>
#include "str_42.h"
#include "ft_printf.h"
#include "parser.h"

static void	parser_set_error(const t_parser *parser, int err)
{
	const t_token	*token;
	const char		*token_name;
	char			*token_word;

	if (err == ERR_PARSING)
	{
		token = parser_get_current_token(parser);
		token_name = lexer_debug_get_token_name(token->type);
		token_word = ft_strsub(parser->input->str, token->start, token->len);
		error_set_context("unexpected token %s: %s",
				token_name, token_word);
		free(token_word);
	}
}

int		parser_parse(t_parser *parser)
{
	int	ret;

	ret = predict_program(parser, &parser->ast.root);
	if (ret != PARSER_NO_ERROR)
	{
		parser_set_error(parser, ret);
		return (ret);
	}
	ret = parser_consume_if_match(parser, E_TOKEN_END_OF_INPUT);
	if (ret != PARSER_NO_ERROR)
	{
		parser_set_error(parser, ret);
		return (ret);
	}
	ast_compress(&parser->ast);
	return (PARSER_NO_ERROR);
}
