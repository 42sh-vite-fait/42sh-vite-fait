#include "alias.h"

extern t_alias	g_alias;
t_alias			g_alias;

int				alias_init(void)
{
	if (array_init(&g_alias.aliases, sizeof(t_string)) == NULL)
		return (-1);
	return (0);
}

void			alias_shutdown(void)
{
	t_string	old;

	while (g_alias.aliases.len != 0)
	{
		array_pop(&g_alias.aliases, &old);
		string_shutdown(&old);
	}
	array_shutdown(&g_alias.aliases);
}
