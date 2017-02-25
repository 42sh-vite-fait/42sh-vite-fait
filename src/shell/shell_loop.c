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
#define INVALID_ 2

int	shell_lex(t_string *input, t_lexer *lexer, t_array *tokens)
{
	int			lexer_status;
	int			input_status;
	t_string	line;
	const char	*prompt;

	lexer_status = LEXER_INPUT_INCOMPLETE;
	prompt = SHELL_PS1;
	string_init(&line);
	while (lexer_status == LEXER_INPUT_INCOMPLETE)
	{
		string_truncate(&line, 0);
		input_status = shell_input(&line, prompt);
		if (input_status != E_INPUT_OK)
			break ;
		lexer_status = lexer_lex(lexer, tokens, &line);
		if (lexer_status != LEXER_ERROR)
			string_append(input, &line);
		prompt = SHELL_PS2;
	}
	string_shutdown(&line);
	if (input_status != E_INPUT_OK)
		return (input_status);
	if (lexer_status == LEXER_ERROR)
	{
		error_print("lexer");
		return (INVALID_);
	}
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
	{
		error_print("parser");
		return (INVALID_);
	}
	return (OK_);
}

int shell_loop(void)
{
	t_string	input;
	t_array		tokens;
	t_parser	parser;
	t_lexer		lexer;
	int			input_parsing_status;
	int			exit_status;

	fatal_malloc(string_init(&input));
	fatal_malloc(array_init(&tokens, sizeof(t_token)));
	fatal_malloc(parser_init(&parser));
	fatal_malloc(lexer_init(&lexer));

	exit_status = 0;
	while (1)
	{
		string_truncate(&input, 0);
		string_shrink_to_fit(&input);
		array_clear(&tokens);
		parser_clear(&parser);

		input_parsing_status = shell_parse(&input, &lexer, &tokens, &parser);
		if (input_parsing_status == OK_)
		{
			// TODO: cut lines multiple lines before pushing in history
			if (opt_is_set(OPT_INTERACTIVE))
				history_add(fatal_malloc(string_create_dup(input.str)));
			if (opt_is_set(OPT_DEBUG_INPUT))
				ft_printf("INPUT: [%s]\n", input.str);
			if (opt_is_set(OPT_DEBUG_LEXER))
				lexer_debug_print_tokens(&input, &tokens);
			if (opt_is_set(OPT_DEBUG_AST))
				ast_debug_print(&parser.ast, input.str);
		}
		else if (input_parsing_status == EOF_)
		{
			if (!assert_stack_is_empty(&lexer)) // Unfinished lexing
				error_print("lexer");
			break ;
		}
		else if (input_parsing_status == INVALID_)
		{
			if (!opt_is_set(OPT_INTERACTIVE))
			{
				exit_status = 1;
				break ;
			}
		}
		else if (input_parsing_status == ERROR_)
		{
			exit_status = 1;
			break ;
		}
		/* if (shell_exec(parser->ast) != EXEC_NO_ERROR) */
		/*	return (EXIT_FAILURE); */
	}

	// Faire des trucs avant de quitter, genre historique tout ca.
	string_shutdown(&input);
	array_shutdown(&tokens);
	parser_shutdown(&parser);
	return (input_parsing_status);
}
