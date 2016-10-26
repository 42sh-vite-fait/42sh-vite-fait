#include "input.h"

char	*input_readline()
{
	t_string	input;
	char		c;

	string_init(&input);
	while (read(0, &c, 1) != -1)
	{
		if (c == '\n')
			break ;
		string_ncat(&input, &c, 1);
	}
	return (input.str);
}
