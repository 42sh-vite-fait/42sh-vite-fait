#include <stdbool.h>
#include "ft_printf.h"
#include "array_42.h"
#include "builtin.h"
#include "str_42.h"
#include "alias.h"

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

uint8_t			builtin_alias(int argc, char * const *argv)
{
	ssize_t		equal_pos;
	const char	*value;
	char		*name_value;
	int			i;
	uint8_t		ret;

	ret = 0;
	i = 1;
	while (i < argc)
	{
		// TODO if a string starts with '-' parse all other arguments as options
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == 'p' && argv[i][2] == '\0') // TODO clean this
			{
				list_aliases();
			}
			else
			{
				ret = 1;
				ft_dprintf(2, "alias: %s: invalid option\n", argv[i]);
				ft_dprintf(2, "alias: usage: alias [-p] [name[=value] ... ]\n");
			}
		} // if '=' is the first letter, use has
		else if ((equal_pos = ft_strchrpos(argv[i], '=')) != -1)
		{
			if (is_valid_alias_name(argv[i], (size_t)equal_pos) == false)
			{
				ret = 1;
				// argv[i][equal_pos] = '\0';
				ft_dprintf(2, "alias: '%s': invalid alias name\n", argv[i]); // TODO limit str len
			}
			else if (alias_set(name_value = ft_strdup(argv[i])) == -1) // TODO abc='coucou les potes'
			{
				free(name_value);
				ret = 1;
				ft_dprintf(2, "alias: error while trying to set '%s'\n", argv[i]); // TODO limit str len
			}
		}
		else
		{
			if ((value = alias_get_value(argv[i])) == NULL)
			{
				ret = 1;
				ft_dprintf(2, "%s: %s: not found\n", argv[0], argv[1]);
			}
			else
			{
				ft_printf("alias %s='%s'\n", argv[i], value);
			}
		}
		++i;
	}
	return (ret);
}
