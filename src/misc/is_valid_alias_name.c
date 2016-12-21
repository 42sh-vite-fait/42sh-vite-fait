#include <stdbool.h>
#include <stdlib.h>
#include "ctype_42.h"
#include "misc.h"

#define IS_VALID_ALIAS_NAME_CHAR(x) (FT_ISALNUM(x) || (x == '!' || x == '%' || x == '@' || x == ',' || x == '_'))

bool	is_valid_alias_name(const char *string, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (!IS_VALID_ALIAS_NAME_CHAR(string[i]))
			return false;
		i++;
	}
	return true;
}
