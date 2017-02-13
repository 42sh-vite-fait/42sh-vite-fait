#include "string_42.h"
#include "opt.h"
#include "input.h"
#include "history.h"
#include "shell.h"
#include "lexer.h"

static int shell_lexer_request_more(t_string *input, t_lexer *lexer,
		t_array *tokens)
{
	t_string	line;
	int			input_status;
	int			lexer_status;

	input_status = shell_input(&line, SHELL_PS2); // TODO: PS2
	if (input_status == E_INPUT_EOF)
	{
		if (!assert_stack_is_empty(lexer))
			error_print("lexer");
		else
			exit(0);
	}
	if (input_status != E_INPUT_OK)
		exit(1);
	lexer_status = lexer_lex(lexer, tokens, &line);
	if (line.len > 0)
	{
		if (opt_is_set(OPT_INTERACTIVE))
			history_add(fatal_malloc(string_create_dup(line.str)));
		string_append(input, &line);
	}
	string_shutdown(&line);
	return (lexer_status);
}

int	shell_lexer(t_string *input, t_array *tokens)
{
	t_lexer	lexer;
	int		status;

	fatal_malloc(lexer_init(&lexer));
	status = lexer_lex(&lexer, tokens, input);
	while (status == LEXER_INPUT_INCOMPLETE)
		status = shell_lexer_request_more(input, &lexer, tokens);
	if (status == LEXER_ERROR)
	{
		error_set_context("lexing error !");
		error_print("lexer");
		string_shutdown(input);
	}
	else if (opt_is_set(OPT_DEBUG_LEXER))
		lexer_debug_print_tokens(input, tokens);
	lexer_shutdown(&lexer);
	return (status);
}
