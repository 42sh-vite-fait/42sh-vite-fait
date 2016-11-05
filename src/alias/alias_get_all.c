#include "alias.h"
#include "string_42.h"
#include "array_42.h"

extern t_alias	g_alias;

const t_array	*alias_get_all(void)
{
	return (&g_alias);
}
