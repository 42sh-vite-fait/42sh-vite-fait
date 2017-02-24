#include "string_42.h"
#include "ft_printf.h"
#include "shell.h"
#include "lexer.h"
#include "opt.h"
#include "input.h"

int	shell_input(t_string *input, int status)
{
	int			ret;
	const char	*prompt;

	if (status == INPUT_REQUEST)
		prompt = SHELL_PS1;
	else
		prompt = SHELL_PS2;
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
	return (ret);
}
