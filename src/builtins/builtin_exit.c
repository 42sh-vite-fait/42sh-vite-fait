#include <stdlib.h>
#include <stdbool.h>
#include "exit_status.h"
#include "stdlib_42.h"
#include "errors.h"
#include "ctype_42.h"

static bool	is_only_digits(const char *s)
{
	while (*s && FT_ISDIGIT(*s))
		s += 1;
	return (*s == '\0' ? true : false);
}

int builtin_exit(int ac, char * const *av, char * const *env)
{
	int	exit_status;

	(void)env;
	if (ac > 2)
	{
		error_set_context("too many arguments");
		error_print("exit");
		exit_status = 1;
	}
	else if (ac == 1)
		exit_status = exit_status_get_last();
	else if (is_only_digits(av[1]))
		exit_status = (unsigned char)ft_atou(av[1]);
	else
		exit_status = 255;
	exit(exit_status);
}
