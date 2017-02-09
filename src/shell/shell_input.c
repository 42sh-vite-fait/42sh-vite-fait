#include "string_42.h"
#include "ft_printf.h"
#include "shell.h"
#include "lexer.h"
#include "opt.h"
#include "input.h"

int	shell_input(t_string *input, const char *prompt)
{
	int	status;

	status = input_get_line(input, prompt);
	if (status != E_INPUT_OK)
		return (status);
	while (remove_trailing_escaped_newline(input) != LINE_COMPLETE)
	{
		string_shutdown(input);
		status = input_get_line(input, prompt);
		if (status != E_INPUT_OK)
			return (status);
	}
	if (opt_is_set(OPT_DEBUG_INPUT))
		ft_printf("INPUT: [%s]\n", input->str);
	return (status);
}
