#include "ctype_42.h"
#include "str_42.h"

char	*ft_strtoupper(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		str[i] = FT_TOUPPER(str[i]);
		++i;
	}
	return (str);
}
