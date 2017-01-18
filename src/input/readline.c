#include "input.h"
#include "user_interface.h"

t_string	input_get_delim(void)
{
	return ((t_string){0, 0, 0});
}

t_string input_get_line(const char *prompt)
{
	t_string input;

	input.str = NULL;
	if (isatty(STDIN_FILENO))
		input = ui_get_user_input(prompt);
	else
		input = input_get_delim();
	return (input);
}
