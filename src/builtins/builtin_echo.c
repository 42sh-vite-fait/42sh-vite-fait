#include <stdbool.h>
#include "string_42.h"
#include "str_42.h"
#include "error_42.h"
#include "ft_printf.h"
#include "builtins.h"

int		builtin_echo(int argc, const char *const *argv)
{
	t_string	buf;
	bool		newline;

	(void)argc;
	argv += 1;
	newline = true;
	if (ft_strcmp(*argv, "-n") == 0)
	{
		newline = false;
		argv += 1;
	}
	fatal_malloc(string_init(&buf));
	while (*argv)
	{
		fatal_malloc(string_cat(&buf, *argv));
		if (argv[1] != NULL)
			fatal_malloc(string_ncat(&buf, " ", 1));
		argv += 1;
	}
	if (newline)
		ft_printf("%s\n", buf.str);
	else
		ft_printf("%s", buf.str);
	string_shutdown(&buf);
	return (0);
}
