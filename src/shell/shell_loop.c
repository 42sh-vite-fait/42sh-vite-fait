#include "string_42.h"
#include "array_42.h"
#include "history.h"
#include "parser.h"
#include "shell.h"

static void	shell_struct_init(t_array *tokens, t_parser *parser)
{
	fatal_malloc(array_init(tokens, sizeof(t_token)));
	fatal_malloc(parser_init(parser));
}

static void	shell_struct_clear(t_array *tokens, t_parser *parser)
{
	array_clear(tokens);
	parser_clear(parser);
}

static void	shell_struct_shutdown(t_array *tokens, t_parser *parser)
{
	array_shutdown(tokens);
	parser_shutdown(parser);
}

void shell_loop(void)
{
	t_string	input;
	t_array		tokens;
	t_parser	parser;

	shell_struct_init(&tokens, &parser);
	while (42)
	{
		shell_struct_clear(&tokens, &parser);
		if (shell_input(&input) == NULL)
			break ;
		if (input.len == 0)
			continue ;
		history_add(fatal_malloc(string_create_dup(input.str)));
		if (shell_lexer(&input, &tokens) == LEXER_ERROR)
			continue ;
		if (shell_parser(&parser, &tokens) != PARSER_NO_ERROR)
			continue ;
		/* if (shell_exec(parser.ast) != EXEC_NO_ERROR) */
		/* 	continue ; */
		string_shutdown(&input);
	}
	shell_struct_shutdown(&tokens, &parser);
}
