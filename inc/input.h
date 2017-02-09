#ifndef INPUT_H
# define INPUT_H

# include <unistd.h>
# include <assert.h>
# include "string_42.h"
# include "opt.h"

enum e_input_status
{
	E_INPUT_EOF,
	E_INPUT_ERROR,
	E_INPUT_OK,
};

int	input_get_line(t_string *input, const char *prompt);

#endif
