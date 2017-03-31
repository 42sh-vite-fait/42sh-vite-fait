#include "string_42.h"
#include "ft_printf.h"
#include "shell.h"
#include "lexer.h"
#include "opt.h"
#include "input.h"
#include "sig.h"
#include "expansion.h"

int	shell_input(t_string *line, const char *prompt)
{
	int			ret;
	bool		is_line_complete;
	t_string	current_line;

	is_line_complete = false;
	fatal_malloc(string_init(&current_line));
	while (!is_line_complete)
	{
		ret = input_get_line(&current_line, prompt);
		if (ret != OK_)
			break ;
		if (remove_trailing_escaped_newline(&current_line) == LINE_COMPLETE)
			is_line_complete = true;
		fatal_malloc(string_append(line, &current_line));
		string_truncate(&current_line, 0);
		prompt = SHELL_PS2;
	}
	if (expand_history(line) == ERROR_)
		return (CMD_DROP_);
	string_shutdown(&current_line);
	if (opt_is_set(OPT_DEBUG_INPUT) && ret == OK_) // DEBUG
		ft_printf("INPUT: [%s]\n", line->str);
	return (ret);
}
