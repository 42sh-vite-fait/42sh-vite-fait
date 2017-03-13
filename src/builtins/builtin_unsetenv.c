#include <assert.h>
#include <stdbool.h>
#include "var.h"
#include "misc.h"
#include "ft_printf.h"

static void	unset_args(const char *const *argv)
{
	while (*argv)
	{
		if (ft_strcmp(*argv, "*") == 0)
		{
			var_clear();
			return ;
		}
		if (is_valid_name(*argv, ft_strlen(*argv)))
			var_unset(*argv);
		argv += 1;
	}
}

static bool	unsetenv_is_args_valid(int argc)
{
	if (argc == 1)
	{
		error_set_context("too few arguments");
		return (false);
	}
	return (true);
}

int			builtin_unsetenv(int argc, const char *const *argv)
{
	if (!unsetenv_is_args_valid(argc))
	{
		error_print("unsetenv");
		return (1);
	}
	unset_args(argv + 1);
	return (0);
}
