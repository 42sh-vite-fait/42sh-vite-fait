#ifndef INPUT_H
# define INPUT_H

# include <unistd.h>
# include <assert.h>
# include "string_42.h"
# include "opt.h"

enum e_input_status // TODO migrate to errors.h
{
	E_INPUT_ERROR = -1,
	E_INPUT_EOF = 0,
	E_INPUT_COMPLETE = 1,
	E_INPUT_INCOMPLETE = 2,
	E_INPUT_OK = E_INPUT_COMPLETE,
};

#define INPUT_REQUEST_MORE	1
#define INPUT_REQUEST		0

int	input_get_line(t_string *input, const char *prompt);

#endif
