#include "string_42.h"
#include "array_42.h"
#include "history.h"
#include "parser.h"
#include "shell.h"
#include "opt.h"
#include "input.h"
#include "ft_printf.h"

#define EOF_ 0
#define ERROR_ -1
#define OK_ 1

int	shell_lex(t_string *input, t_lexer *lexer, t_array *tokens)
{
	int			lexer_status;
	int			input_status;
	t_string	line;

	lexer_status = LEXER_INPUT_INCOMPLETE;
	string_init(&line);
	while (lexer_status == LEXER_INPUT_INCOMPLETE)
	{
		string_truncate(&line, 0);
		// TODO: INPUT_REQUEST_MORE if input incomplete
		input_status = shell_input(&line, INPUT_REQUEST);
		if (input_status != E_INPUT_OK)
			return (input_status) ;
		lexer_status = lexer_lex(lexer, tokens, &line);
		if (lexer_status != LEXER_ERROR)
			string_append(input, &line);
	}
	if (lexer_status == LEXER_ERROR)
		error_print("lexer");
	string_shutdown(&line);
	return (OK_);
}

int shell_parse(t_string *input, t_lexer *lexer, t_array *tokens,
				t_parser *parser)
{
	int	lexer_status;
	int	parser_status;

	lexer_status = shell_lex(input, lexer, tokens);
	if (lexer_status != OK_)
		return (lexer_status);
	categorize_tokens(input, tokens);
	lexer_clear_tokens(tokens);
	parser_init_with_tokens(input, parser, tokens);
	parser_status = parser_parse(parser);
	if (parser_status != PARSER_NO_ERROR)
		error_print("parser");
	return (OK_);
}

int shell_loop(void)
{
	t_string	input;
	t_array		tokens;
	t_parser	parser;
	t_lexer		lexer;
	int			ret;

	fatal_malloc(string_init(&input));
	fatal_malloc(array_init(&tokens, sizeof(t_token)));
	fatal_malloc(parser_init(&parser));
	fatal_malloc(lexer_init(&lexer));

	while (1)
	{
		string_truncate(&input, 0);
		string_shrink_to_fit(&input);
		array_clear(&tokens);
		parser_clear(&parser);

		// TODO: error handling in non-interactive mode
		ret = shell_parse(&input, &lexer, &tokens, &parser);
		if (ret == OK_)
		{
			// TODO: cut lines multiple lines before pushing in history
			if (opt_is_set(OPT_INTERACTIVE))
				history_add(fatal_malloc(string_create_dup(input.str)));
			if (opt_is_set(OPT_DEBUG_INPUT))
				ft_printf("INPUT: [%s]\n", input.str); // A mettre plus loin
			if (opt_is_set(OPT_DEBUG_LEXER))
				lexer_debug_print_tokens(&input, &tokens);
			if (opt_is_set(OPT_DEBUG_AST))
				ast_debug_print(&parser.ast, input.str);
		}
		else if (ret == EOF_)
		{
			// Faire des trucs avant de quitter, genre historique tout ca.
			if (!assert_stack_is_empty(&lexer)) // Unfinished lexing
				error_print("lexer");
			exit(0);
		}
		else if (ret == ERROR_)
		{
			// Faire des trucs avant de quitter, genre historique tout ca.
			exit(1);
		}
		/* if (shell_exec(parser->ast) != EXEC_NO_ERROR) */
		/*	return (EXIT_FAILURE); */
	}

	// Faire ca avant de quitter
	string_shutdown(&input);
	array_shutdown(&tokens);
	parser_shutdown(&parser);
	return (ret);
}
