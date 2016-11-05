#include "alias.h"
#include "string_42.h"
#include "array_42.h"

extern t_alias	g_alias;
t_alias			g_alias;

int				alias_init(void)
{
	if (array_init(&g_alias, sizeof(t_string)) == NULL)
		return (-1);
	return (0);
}

void			alias_shutdown(void)
{
	alias_clear();
	array_shutdown(&g_alias);
}
