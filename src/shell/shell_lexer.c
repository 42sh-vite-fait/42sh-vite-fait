#include "string_42.h"
#include "opt.h"
#include "input.h"
#include "history.h"
#include "shell.h"

static int shell_lexer_request_more(t_string *input, t_lexer *lexer,
		t_array *tokens)
{
	t_string	line;
	int			status;

	line = input_get_line(SHELL_PS2);
	status = lexer_lex(lexer, tokens, line.str);
	if (line.len > 0)
	{
		history_add(fatal_malloc(string_create_dup(line.str)));
		string_append(input, &line);
	}
	string_shutdown(&line);
	return (status);
}

int	shell_lexer(t_string *input, t_array *tokens)
{
	t_lexer	lexer;
	int		status;

	fatal_malloc(lexer_init(&lexer));
	status = lexer_lex(&lexer, tokens, input->str);
	while (status == LEXER_INPUT_INCOMPLETE)
		status = shell_lexer_request_more(input, &lexer, tokens);
	if (status == LEXER_ERROR)
	{
		error_set_context("lexing error !");
		string_shutdown(input);
	}
	if (opt_is_set(OPT_DEBUG_LEXER))
		lexer_debug_print_tokens(tokens);
	lexer_shutdown(&lexer);
	return (status);
}
