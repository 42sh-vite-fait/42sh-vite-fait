#ifndef INPUT_H
# define INPUT_H

# include <unistd.h>
# include <assert.h>
# include "string_42.h"
# include "opt.h"

enum e_input_status
{
	E_INPUT_ERROR = -1,
	E_INPUT_EOF = 0,
	E_INPUT_OK = 1,
};

int	input_get_line(t_string *input, const char *prompt);

#endif
