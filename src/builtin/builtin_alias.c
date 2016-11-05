#include "unistd_42.h"
#include "ft_printf.h"
#include "builtin.h"
#include "alias.h"
#include "str_42.h"

static int	list_aliases(void)
{
	// const t_string	*command;
	// size_t			i;
	// size_t			last_id;

	// i = 1;
	// last_id = history_get_last_id();
	// while (i <= last_id)
	// {
	// 	command = history_get(i);
	// 	if (command == NULL)
	// 		return (1);
	// 	if (ft_printf("%5zu  %s\n", i, command->str) == -1)
	// 		return (1);
	// 	++i;
	// }
	return (0);
}

uint8_t		builtin_alias(int argc, char * const *argv)
{
	t_string	alias;
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
			fatal_malloc(string_dup(&alias, argv[1]));
			return ((uint8_t)alias_set(&alias)); // TODO check return value
		}
		else
		{
			fatal_malloc(string_dup(&alias, argv[1]));
			value = alias_get_value(&alias);
			string_shutdown(&alias);
			if (value != NULL)
			{
				ft_printf("%s=%s\n", argv[1], value);
				return (0);
			}
			else
				ft_dprintf(2, "42sh: %s: %s: not found\n", argv[0], argv[1]); // TODO define for "42sh"
		}
	}
	return (1);
}
