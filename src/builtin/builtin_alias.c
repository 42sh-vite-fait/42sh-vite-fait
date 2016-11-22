#include <stdbool.h>
#include "ft_printf.h"
#include "array_42.h"
#include "builtin.h"
#include "str_42.h"
#include "alias.h"
#include "unistd_42.h"

static void		list_aliases(void)
{
	const t_array	*aliases;
	size_t			i;

	i = 0;
	aliases = alias_get_all();
	while (i < aliases->len)
	{
		ft_printf("%s\n", *(char**)array_get_at(aliases, i));
		++i;
	}
}

// TODO define valid alias !!!
static bool		is_valid_alias_name(const char *name, size_t len)
{
	size_t		i;

	if (name[0] == '-' || FT_ISDIGIT(name[0]))
		return (false);
	i = 1;
	while (i < len)
	{
		if (!FT_ISALNUM(name[i]))
			return (false);
		++i;
	}
	return (true);
}

static uint8_t	getset_arguments(int count, char * const * args)
{
	ssize_t		equal_pos;
	const char	*value;
	int			i;
	uint8_t		ret;

	ret = 0;
	i = 0;
	while (i < count)
	{
		if ((equal_pos = ft_strchrpos(args[i], '=')) != -1)
		{
			if (is_valid_alias_name(args[i], (size_t)equal_pos) == false)
			{
				ret = 1;
				// args[i][equal_pos] = '\0';
				ft_dprintf(2, "alias: '%s': invalid alias name\n", args[i]); // TODO display only name
			}
			else
			{
				alias_set(ft_strdup(args[i]));
			}
		}
		else
		{
			if ((value = alias_get_value(args[i])) == NULL)
			{
				ret = 1;
				ft_dprintf(2, "%s: %s: not found\n", args[0], args[1]);
			}
			else
			{
				ft_printf("alias %s='%s'\n", args[i], value);
			}
		}
		++i;
	}
	return (ret);
}

uint8_t			builtin_alias(int argc, char * const *argv)
{
	int			ret;
	t_opt		state;

	ft_bzero(&state, sizeof(*state)); // TODO replace by GETOPT_INIT
	while ((ret = ft_getopt(argc, argv, "p", &state)) != -1)
	{
		if (state.optopt == 'p')
		{
			list_aliases();
			return (0);
		}
		else if (ret == '?')
		{
			ft_dprintf(2, "alias: -%c: invalid option\n", state.optopt);
			ft_dprintf(2, "alias: usage: alias [-p] [name[=value] ... ]\n");
			return (1);
		}
	}
	return (getset_arguments(argc - state.optind + 1, argv + state.optind));
}
