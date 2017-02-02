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

static void	shell_struct_clear(t_string *input, t_array *tokens, t_parser *parser)
{
	array_clear(tokens);
	parser_clear(parser);
	string_shutdown(input);
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
		// input
		shell_input(&input);
		if (input.str == NULL || input.len == 0)
		{
			write(1, "\n", 1);
			continue ;
		}

		// history
		history_add(fatal_malloc(string_create_dup(input.str)));

		// lexer
		if (shell_lexer(&input, &tokens) == LEXER_ERROR)
		{
			error_print("lexer");
			continue ;
		}

		// parser
		if (shell_parser(&parser, &tokens) != PARSER_NO_ERROR)
		{
			error_print("parser");
			continue ;
		}

		// exec

		// post exec
		shell_struct_clear(&input, &tokens, &parser);
	}
	shell_struct_shutdown(&tokens, &parser);
}
