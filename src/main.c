// #include <string.h>
// #include <unistd.h>
// #include <stdlib.h>

#include "user_interface.h"

int		main(void)
{
	int i = -1;

	while (i--)
		if (get_line() == NULL)
			break ;
	//read(1, b, 10);
	return (0);
}
