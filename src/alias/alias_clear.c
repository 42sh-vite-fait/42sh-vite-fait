#include "alias.h"
#include "string_42.h"
#include "array_42.h"

extern t_alias	g_alias;

void		alias_clear(void)
{
	t_string	old;

	while (g_alias.len != 0)
	{
		array_pop(&g_alias, &old);
		string_shutdown(&old);
	}
}
