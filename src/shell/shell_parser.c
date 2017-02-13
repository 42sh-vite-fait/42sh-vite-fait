#include "array_42.h"
#include "opt.h"
#include "parser.h"
#include "ast.h"
#include "shell.h"

int shell_parser(const t_string *input, t_parser *parser, const t_array *tokens)
{
	int	ret;

	parser_init_with_tokens(input, parser, tokens);
	ret = parser_parse(parser);
	if (ret != PARSER_NO_ERROR)
		error_print("parser");
	else if (opt_is_set(OPT_DEBUG_AST))
		ast_debug_print(&parser->ast, input->str);
	return (ret);
}
