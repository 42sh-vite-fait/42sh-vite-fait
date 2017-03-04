#include "string_42.h"
#include "ft_printf.h"
#include "shell.h"
#include "lexer.h"
#include "opt.h"
#include "input.h"

int	shell_input(t_string *input, const char *prompt)
{
	int			ret;

	ret = E_INPUT_INCOMPLETE;
	while (ret == E_INPUT_INCOMPLETE)
	{
		ret = input_get_line(input, prompt);
		if (ret == E_INPUT_OK)
		{
			if (remove_trailing_escaped_newline(input) != LINE_COMPLETE)
				ret = E_INPUT_INCOMPLETE;
		}
		prompt = SHELL_PS2;
	}
	if (opt_is_set(OPT_DEBUG_INPUT) && ret == E_INPUT_OK) // DEBUG
		ft_printf("INPUT: [%s]\n", input->str);
	return (ret);
}
