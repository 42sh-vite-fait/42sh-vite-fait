#include <assert.h>
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
		token_word = ft_strsub(token->str, 0, token->len);
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

void	parser_init(t_parser *parser, t_array *tokens)
{
	assert(!ARRAY_IS_EMPTY(tokens));
	assert(parser != NULL);
	ast_init(&parser->ast);
	parser->tokens = tokens;
	parser->current_token = array_get_first(tokens);
	parser->index = 0;
	parser->subshell_depth = 0;
}

void	parser_shutdown(t_parser *parser)
{
	ast_shutdown(&parser->ast);
	ft_memset(parser, 0, sizeof(*parser));
}
