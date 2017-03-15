#include <stdlib.h>
#include <stdbool.h>
#include "exit_status.h"
#include "stdlib_42.h"
#include "errors.h"
#include "ctype_42.h"

static bool	is_only_digits(const char *s)
{
	while (FT_ISDIGIT(*s))
		s += 1;
	return (*s == '\0' ? true : false);
}

static bool	is_errors_in_args(int ac, const char *arg)
{
	if (ac > 2)
	{
		error_set_context("too many arguments");
		return (true);
	}
	else if (!is_only_digits(arg))
	{
		error_set_context("%s: bad number", arg);
		return (true);
	}
	return (false);
}

int builtin_exit(int ac, const char * const *av)
{
	int	exit_status;

	if (ac == 1)
		exit_status = exit_status_get_last();
	else if (is_errors_in_args(ac, av[1]))
	{
		error_print("exit");
		return (1);
	}
	else
		exit_status = (unsigned char)ft_atou(av[1]);
	exit(exit_status);
}
