#include "unistd_42.h"
#include "ft_printf.h"
#include "builtin.h"
#include "alias.h"
#include "str_42.h"

uint8_t		builtin_unalias(int argc, char * const *argv)
{
	t_opt		opt;
	int			i;
	uint8_t		ret;

	if (argc == 1)
	{
		ft_dprintf(2, "unalias: usage: unalias [-a] name [name ...]");
		return (2);
	}
	OPT_INIT(opt);
	if (ft_getopt(argc, argv, "a", &opt) == 'a')
	{
		alias_clear();
		return (0);
	}
	ret = 0;
	i = 1;
	while (i < argc)
	{
		if (alias_unset(argv[i]) != 0)
		{
			ret = 1;
			ft_dprintf(2, "unalias: %s: not found\n", argv[i]);
		}
		++i;
	}
	return (ret);
}
