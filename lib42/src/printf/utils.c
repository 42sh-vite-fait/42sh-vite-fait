#include "ft_printf.h"

void	exit_printf(int code)
{
	write(2, "malloc error\n", 13);
	exit(code);
}

int		cleanup_buf(t_string *pb)
{
	free(pb->str);
	return (-1);
}
