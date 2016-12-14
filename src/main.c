#include "input.h"
#include "lexer.h"
#include "ft_printf.h"
#include "array_42.h"

static t_string	wrap_get_line()
{
	t_string	input;

	input = input_get_line(E_INTERACTIVE);
	if (input.str == NULL)
		exit(0);
	return (input);
}

int		main(void)
{
	t_lexer		lexer;
	t_array		tokens;
	t_string	input;
	int			status;

	lexer_init(&lexer);
	array_init(&tokens, sizeof(t_token));
	while (42)
	{
		// first input
		input = wrap_get_line();
		while (remove_trailing_escaped_newline(&input))
			input = wrap_get_line();

		// lexer
		status = lexer_lex(&lexer, &tokens, input.str);
		while (true)
		{
			if (status == LEXER_ERROR)
				return (ft_printf("LEXING ERROR\n"), 1);
			else if (status == LEXER_INPUT_COMPLETE)
				break ;
			else if (status == LEXER_INPUT_INCOMPLETE)
			{
				t_string tmp = wrap_get_line();
				status = lexer_lex(&lexer, &tokens, tmp.str);
				string_append(&input, &tmp);
				string_shutdown(&tmp);
			}
		}

		// debug
		ft_printf("INPUT: %s\n\n", input.str);
		lexer_debug_print_tokens(&tokens, input.str);

		// shall we exit ?
		if (ft_strcmp(input.str, "exit") == 0)
			break ;

		// reset struct
		string_shutdown(&input);
		array_clear(&tokens);
	}
	lexer_shutdown(&lexer);
}
