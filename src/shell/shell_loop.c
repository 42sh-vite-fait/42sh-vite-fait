#include "string_42.h"
#include "array_42.h"
#include "history.h"
#include "parser.h"
#include "shell.h"
#include "opt.h"
#include "input.h"

static void	shell_struct_clear(t_string *input, t_array *tokens, t_parser *parser)
{
	string_truncate(input, 0);
	string_shrink_to_fit(input);
	array_clear(tokens);
	parser_clear(parser);
}

static int	get_input(t_string *input, char const *prompt)
{
	int	status;
	if (opt_is_set(OPT_INTERACTIVE))
	{
		while (1)
		{
			status = shell_input(input, prompt);
			if (status != E_INPUT_ERROR)
				break ;
			history_add(fatal_malloc(string_create_dup(input->str)));
			if (input->len == 0)
				continue;
		}
	}
	else
		status = shell_input(input, prompt);
	return (status);
}

static int	loop_on_command_lines(t_string *input, t_array *tokens, t_parser *parser)
{
	int	input_status;

	input_status = E_INPUT_OK;
	while (1)
	{
		shell_struct_clear(input, tokens, parser);
		input_status = get_input(input, SHELL_PS1);
		if (input_status == E_INPUT_ERROR)
			return (EXIT_FAILURE);
		if (input_status == E_INPUT_EOF)
			return (EXIT_SUCCESS);
		if (shell_lexer(input, tokens) == LEXER_ERROR)
			return (EXIT_FAILURE);
		if (shell_parser(input, parser, tokens) != PARSER_NO_ERROR)
			return (EXIT_FAILURE);
		/* if (shell_exec(parser->ast) != EXEC_NO_ERROR) */
		/*	return (EXIT_FAILURE); */
	}
}

int 		shell_loop(void)
{
	t_string	input;
	t_array		tokens;
	t_parser	parser;
	int			ret;

	fatal_malloc(string_init(&input));
	fatal_malloc(array_init(&tokens, sizeof(t_token)));
	fatal_malloc(parser_init(&parser));
	ret = loop_on_command_lines(&input, &tokens, &parser);
	string_shutdown(&input);
	array_shutdown(&tokens);
	parser_shutdown(&parser);
	return (ret);
}
