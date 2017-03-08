#include "string_42.h"
#include "array_42.h"
#include "history.h"
#include "parser.h"
#include "shell.h"
#include "opt.h"
#include "exec.h"
#include "input.h"
#include "ft_printf.h"
#include "exit_status.h"

#define EOF_ 0
#define ERROR_ -1
#define OK_ 1
#define INVALID_ 2

static int	shell_lex(t_string *input, t_lexer *lexer, t_array *tokens)
{
	int			lexer_status;
	int			input_status;
	t_string	line;
	const char	*prompt;

	prompt = SHELL_PS1;
	string_init(&line);
	lexer_status = LEXER_INPUT_INCOMPLETE;
	while (lexer_status == LEXER_INPUT_INCOMPLETE &&
			(input_status = shell_input(&line, prompt)) == E_INPUT_OK)
	{
		if ((lexer_status = lexer_lex(lexer, tokens, &line)) != LEXER_ERROR)
			string_append(input, &line);
		string_truncate(&line, 0);
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

static int shell_parse(t_string *input, t_lexer *lexer, t_array *tokens,
						t_parser *parser)
{
	int	lexer_status;
	int	parser_status;

	lexer_status = shell_lex(input, lexer, tokens);
	if (lexer_status != OK_)
		return (lexer_status);
	categorize_tokens(input, tokens);
	lexer_clear_tokens(tokens);
	if (opt_is_set(OPT_DEBUG_LEXER))
		lexer_debug_print_tokens(input, tokens);
	parser_init_with_tokens(input, parser, tokens);
	parser_status = parser_parse(parser);
	if (parser_status != PARSER_NO_ERROR)
	{
		error_print("parser");
		return (INVALID_);
	}
	if (opt_is_set(OPT_DEBUG_AST))
		ast_debug_print(&parser->ast, input->str);
	return (OK_);
}

static int	shell_loop2(t_string *input, t_array *tokens, t_parser *parser,
						t_lexer *lexer)
{
	int	input_parsing_status;

	while (1)
	{
		string_truncate(input, 0);
		string_shrink_to_fit(input);
		array_clear(tokens);
		parser_clear(parser);
		input_parsing_status = shell_parse(input, lexer, tokens, parser);
		if (input_parsing_status == OK_)
		{
			// TODO: cut multiple lines before pushing in history
			if (opt_is_set(OPT_INTERACTIVE))
				history_add(fatal_malloc(string_create_dup(input->str)));
		}
		else if (input_parsing_status == EOF_)
		{
			if (!assert_stack_is_empty(lexer))
				error_print("lexer");
			return (exit_status_get_last());
		}
		else if (input_parsing_status == INVALID_)
		{
			if (!opt_is_set(OPT_INTERACTIVE))
				return (1);
		}
		else if (input_parsing_status == ERROR_)
			return (1);
		exec_ast(parser->ast, input);
		if (opt_is_set(OPT_DEBUG_EXEC))
			ft_printf("EXEC: %d\n", exit_status_get_last());
	}
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
	ret = shell_loop2(&input, &tokens, &parser, &lexer);
	// TODO: Faire des trucs avant de quitter, genre historique tout ca.
	string_shutdown(&input);
	array_shutdown(&tokens);
	lexer_shutdown(&lexer);
	parser_shutdown(&parser);
	return (ret);
}
