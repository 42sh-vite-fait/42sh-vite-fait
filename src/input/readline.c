#include "input.h"
#include "user_interface.h"

t_string input_get_line(unsigned mode)
{
	t_string input;

	input.str = NULL;
	if (mode == E_INTERACTIVE)
		input = ui_get_user_input();
	return (input);
}
