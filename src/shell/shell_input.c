#include "string_42.h"
#include "ft_printf.h"
#include "shell.h"
#include "lexer.h"
#include "opt.h"
#include "input.h"

void	*shell_input(t_string *input)
{
	const char	*cmdline;

	cmdline = opt_get_command_line();
	if (cmdline != NULL)
		fatal_malloc(string_init_dup(input, cmdline));
	else
	{
		*input = input_get_line(SHELL_PS1);
		while (remove_trailing_escaped_newline(input) != LINE_COMPLETE)
		{
			string_shutdown(input);
			*input = input_get_line(SHELL_PS1);
		}
	}
	if (opt_is_set(OPT_DEBUG_INPUT))
		ft_printf("INPUT: [%s]\n", input->str);
	return (input->str);
}
