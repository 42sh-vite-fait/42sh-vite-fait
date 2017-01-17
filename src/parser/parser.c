#include "ft_printf.h"
#include "parser.h"
#include "lexer.h"
#include "ast.h"

int		parser_parse(t_parser *parser)
{
	if (predict_program(parser, &parser->ast.root) != NO_ERROR)
		return (ERR_PARSING);
	if (parser_consume_if_match(parser, E_TOKEN_END_OF_INPUT))
		return (ERR_PARSING);
	ast_compress(&parser->ast);
	return (NO_ERROR);
}

void	parser_print_error(const t_parser *parser)
{
	ft_dprintf(2, "unexpected token %s\n",
			lexer_debug_get_token_name(parser_get_current_token(parser)->type));
}

void	parser_init(t_parser *parser, t_array *tokens)
{
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
