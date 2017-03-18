#include <stdbool.h>
#include <assert.h>
#include "builtins.h"
#include "var.h"
#include "errors.h"
#include "misc.h"

static bool	setenv_is_args_valid(int argc, const char *const *argv)
{
	if (argc >= 4)
	{
		error_set_context("too many arguments");
		return (false);
	}
	else if (argc >= 2 && !is_valid_name(argv[1], ft_strlen(argv[1])))
	{
		error_set_context("%s: not a valid identifier", argv[1]);
		return (false);
	}
	return (true);
}

static void	setenv_print(void)
{
	char *const	*envp;

	envp = var_get_environ();
	while (*envp)
	{
		ft_printf("%s\n", *envp);
		envp += 1;
	}
}

int			builtin_setenv(int argc, const char * const *argv)
{
	int	ret;

	if (!setenv_is_args_valid(argc, argv))
	{
		error_print("setenv");
		return (1);
	}
	if (argc == 1)
	{
		setenv_print();
		return (0);
	}
	else if (argc == 2)
		ret = var_set(argv[1], "");
	else
		ret = var_set(argv[1], argv[2]);
	assert(ret == OK_);
	(void)ret;
	return (0);
}
