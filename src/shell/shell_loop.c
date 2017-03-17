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
#include "errors.h"

static int	shell_lex(t_string *input, t_lexer *lexer, t_array *tokens)
{
	int			lexer_status;
	int			input_status;
	t_string	line;
	const char	*prompt;

	prompt = SHELL_PS1;
	fatal_malloc(string_init(&line));
	lexer_status = LEXER_INPUT_INCOMPLETE;
	while (lexer_status == LEXER_INPUT_INCOMPLETE &&
			(input_status = shell_input(&line, prompt)) == E_INPUT_OK)
	{
		if ((lexer_status = lexer_lex(lexer, tokens, &line)) != LEXER_ERROR)
			fatal_malloc(string_append(input, &line));
		string_truncate(&line, 0);
		prompt = SHELL_PS2;
	}
	string_shutdown(&line);
	if (input_status != E_INPUT_OK)
		return (input_status); // TODO !!!! problem
	if (lexer_status == LEXER_ERROR)
	{
		error_print("lexer");
		return (CMD_INVALID_);
	}
	return (OK_);
}

static int	shell_parse(t_string *input, t_lexer *lexer, t_array *tokens,
						t_parser *parser)
{
	int		lexer_status;
	int		parser_status;

	lexer_status = shell_lex(input, lexer, tokens);
	if (lexer_status != OK_)
		return (lexer_status);
	categorize_tokens(input, tokens);
	lexer_clear_tokens(tokens);
	if (opt_is_set(OPT_DEBUG_LEXER))
		lexer_debug_print_tokens(input, tokens);
	if (tokens->len == 1 &&
		((t_token *)array_get_first(tokens))->type == E_TOKEN_NEWLINE)
		return (CMD_DROP_);
	parser_init_with_tokens(input, parser, tokens);
	parser_status = parser_parse(parser);
	if (parser_status != PARSER_NO_ERROR)
	{
		error_print("parser");
		return (CMD_INVALID_);
	}
	if (opt_is_set(OPT_DEBUG_AST))
		ast_debug_print(&parser->ast, input->str);
	return (OK_);
}

static int	get_command(t_string *input, t_lexer *lexer, t_array *tokens,
						t_parser *parser)
{
	string_truncate(input, 0);
	string_shrink_to_fit(input);
	array_clear(tokens);
	parser_clear(parser);
	return (shell_parse(input, lexer, tokens, parser));
}

static int	shell_loop2(t_string *input, t_array *tokens, t_parser *parser,
						t_lexer *lexer)
{
	int	command_status;

	while (1)
	{
		command_status = get_command(input, lexer, tokens, parser);
		if (command_status == OK_)
		{
			exec_ast(parser->ast, input);
			if (opt_is_set(OPT_DEBUG_EXEC))
				ft_printf("EXEC: %d\n", exit_status_get_last());
		}
		else if (command_status == CMD_EOF_)
		{
			if (!assert_stack_is_empty(lexer))
				error_print("lexer");
			return (exit_status_get_last());
		}
		else if (command_status == ERROR_)
			return (1);
		else if (!opt_is_set(OPT_INTERACTIVE) && command_status == CMD_INVALID_)
			return (1);
		if (opt_is_set(OPT_INTERACTIVE) && command_status != CMD_DROP_)
			history_add(input);
		// TODO unlink heredocs files (doit être call en cas d'echec ou de succes)
	}
}

int			shell_loop(void)
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
	string_shutdown(&input);
	array_shutdown(&tokens);
	lexer_shutdown(&lexer);
	parser_shutdown(&parser);
	return (ret);
}
