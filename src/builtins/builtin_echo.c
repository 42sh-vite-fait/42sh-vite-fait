#include "string_42.h"
#include "ft_printf.h"

int	builtin_echo(int ac, char * const *av, char * const *env)
{
	t_string	out;
	int			i;

	(void)env;
	i = 1;
	fatal_malloc(string_init(&out));
	while (i < ac)
	{
		string_cat(&out, av[i]);
		string_ncat(&out, " ", 1);
		i += 1;
	}
	string_set(&out, out.len - 1, 1, '\n');
	ft_printf("%s", out.str);
	string_shutdown(&out);
	return (0);
}
