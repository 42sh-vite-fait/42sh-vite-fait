#include <stdbool.h>
#include "string_42.h"
#include "str_42.h"
#include "error_42.h"
#include "ft_printf.h"
#include "builtins.h"

static void	concat_args(t_string *buf, const char *const *argv)
{
	bool	newline;

	newline = true;
	if (ft_strcmp(*argv, "-n") == 0)
	{
		newline = false;
		argv += 1;
	}
	while (*argv)
	{
		fatal_malloc(string_cat(buf, *argv));
		if (argv[1] != NULL)
			fatal_malloc(string_ncat(buf, " ", 1));
		argv += 1;
	}
	if (newline)
		fatal_malloc(string_ncat(buf, "\n", 1));
}

int			builtin_echo(int argc, const char *const *argv)
{
	t_string	buf;

	fatal_malloc(string_init(&buf));
	argv += 1;
	if (argc > 1)
		concat_args(&buf, argv);
	ft_printf("%s", buf.str);
	string_shutdown(&buf);
	return (0);
}
