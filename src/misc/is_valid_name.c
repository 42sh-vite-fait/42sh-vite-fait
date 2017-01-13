#include <stdbool.h>
#include <stdlib.h>
#include "ctype_42.h"
#include "misc.h"

#define IS_VALID_NAME_FIRST_CHAR(x) (FT_ISALPHA(x) || x == '_')
#define IS_VALID_NAME_CHAR(x) (IS_VALID_NAME_FIRST_CHAR(x) || FT_ISDIGIT(x))

bool	is_valid_name(const char *string, size_t len)
{
	size_t	i;

	if (len != 0 && !IS_VALID_NAME_FIRST_CHAR(string[0]))
		return false;
	i = 1;
	while (i < len)
	{
		if (!IS_VALID_NAME_CHAR(string[i]))
			return false;
		i++;
	}
	return true;
}
