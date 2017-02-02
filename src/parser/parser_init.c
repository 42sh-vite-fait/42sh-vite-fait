#include <assert.h>
#include "parser.h"
#include "ast.h"
#include "memory_42.h"
#include "array_42.h"

t_parser	*parser_init(t_parser *parser)
{
	assert(parser != NULL);
	if (ast_init(&parser->ast) == NULL)
		return (NULL);
	return (parser);
}

void		parser_init_with_tokens(t_parser *parser, const t_array *tokens)
{
	assert(!ARRAY_IS_EMPTY(tokens));
	assert(parser != NULL);
	parser->tokens = tokens;
	parser->current_token = array_get_first(tokens);
	parser->index = 0;
	parser->subshell_depth = 0;
}

void		parser_clear(t_parser *parser)
{
	ast_clear(&parser->ast);
}

void		parser_shutdown(t_parser *parser)
{
	ast_shutdown(&parser->ast);
}
