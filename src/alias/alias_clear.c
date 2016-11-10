#include "alias.h"
#include "array_42.h"

extern t_alias	g_alias;

void		alias_clear(void)
{
	char	*old;

	while (g_alias.len != 0)
	{
		array_pop(&g_alias, &old);
		free(old);
	}
}
