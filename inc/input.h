#ifndef INPUT_H
# define INPUT_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include "string_42.h"

t_string	input_get_line(const char *prompt);

#endif
