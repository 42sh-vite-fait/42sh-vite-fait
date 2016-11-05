#include "ft_printf.h"
#include "unistd_42.h"
#include "array_42.h"
#include "builtin.h"
#include "str_42.h"
#include "alias.h"

static int	list_aliases(void)
{
	const t_array	*aliases;
	size_t			i;

	aliases = alias_get_all();
	i = 0;
	while (i < aliases->len)
	{
		ft_printf("%s\n", ((t_string*)array_get_at(aliases, i))->str);
		++i;
	}
	return (0);
}

uint8_t		builtin_alias(int argc, char * const *argv)
{
	t_opt		opt;
	const char	*value;

	if (argc == 1 || (argc == 2 && ft_getopt(argc, argv, "p", &opt) == 'p'))
	{
		return ((uint8_t)list_aliases());
	}
	else if (argc == 2)
	{
		if (ft_strchr(argv[1], '=') != NULL)
		{
			return ((uint8_t)-alias_set(argv[1])); // TODO check return value
		}
		else
		{
			if ((value = alias_get_value(argv[1])) != NULL)
			{
				ft_printf("%s=%s\n", argv[1], value);
				return (0);
			}
			ft_dprintf(2, "42sh: %s: %s: not found\n", argv[0], argv[1]); // TODO define for "42sh"
		}
	}
	return (1);
}
