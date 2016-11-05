#include "unistd_42.h"
#include "ft_printf.h"
#include "builtin.h"
#include "alias.h"
#include "str_42.h"

uint8_t		builtin_unalias(int argc, char * const *argv)
{
	t_opt		opt;
	t_string	alias;
	int			i;
	uint8_t		ret;

	if (argc == 1)
	{
		// TODO explain me rules of the first word of error messages
		ft_dprintf(2, "%s: usage: %s [-a] name [name ...]", argv[0]); // TODO define for "42sh"
		return (2);
	}
	else if (argc >= 2)
	{
		if (ft_getopt(argc, argv, "a", &opt) == 'a')
		{
			// TODO remove all aliases !
			return (0);
		}
		ret = 0;
		i = 1;
		while (i < argc)
		{
			fatal_malloc(string_dup(&alias, argv[i]));
			if (alias_unset(&alias) != 0)
			{
				ret = 1;
				ft_dprintf(2, "42sh: %s: %s: not found\n", argv[0], argv[i]); // TODO define for "42sh"
			}
			string_shutdown(&alias);
			++i;
		}
		return (ret);
	}
	return (1);
}
