#include "alias.h"

extern t_alias	g_alias;

const t_string	*alias_get(const char *name)
{
	(void)name;
	//
	return (NULL);
}

int				alias_set(const char *name, const t_string *value)
{
	(void)name;
	(void)value;
	//
	return (-1);
}
