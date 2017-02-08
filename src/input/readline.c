#include "input.h"
#include "user_interface.h"
#include "errors.h"

static t_string	input_non_interactive(void)
{
	t_string	input;
	ssize_t		ret;
	char		c;

	fatal_malloc(string_init(&input));
	while ((ret = read(STDIN_FILENO, &c, 1)) > 0)
	{
		fatal_malloc(string_ncat(&input, &c, 1));
		if (c == '\n')
			break ;
	}
	if (ret == 0 && input.len == 0)
	{
		string_shutdown(&input);
		input.str = NULL;
	}
	else if (ret == -1)
	{
		error_set_context("read: %s", strerror(errno));
		string_shutdown(&input);
		input.str = NULL;
	}
	return (input);
}

t_string	input_get_line(const char *prompt)
{
	t_string	input;

	input.str = NULL;
	if (isatty(STDIN_FILENO))
		input = ui_get_user_input(prompt);
	else
		input = input_non_interactive();
	return (input);
}
