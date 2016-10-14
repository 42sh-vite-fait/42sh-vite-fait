#include <stdbool.h>
#include "typedefs_42.h"
#include "string_42.h"
#include "str_42.h"
#include "misc.h"

bool		is_escaped(const char *pos, const char *end)
{
	size_t		count;

	count = 0;
	pos -= 1;
	while (pos >= end && *pos == '\\')
	{
		++count;
		--pos;
	}
	return (count & 1);
}

t_string		*string_escape_chars(t_string *b, int c)
{
	ssize_t		match_pos;
	size_t		offset;

	offset = 0;
	while ((match_pos = ft_strchrpos(b->str + offset, c)) != -1)
	{
		offset += (size_t)match_pos;
		if (string_insert(b, offset, "\\", 1) == NULL)
			return (NULL);
		offset += 2;
	}
	return (b);
}

t_string		*string_unescape_chars(t_string *b, int c)
{
	static char		pattern[3] = {'\\', '\0', '\0'};
	char			*match;
	size_t			offset;

	offset = 0;
	pattern[1] = (char)c;
	while ((match = ft_strstr(b->str + offset, pattern)) != NULL)
	{
		if (is_escaped(match + 1, b->str + offset))
		{
			offset = (size_t)(match - b->str);
			if (string_remove(b, offset, 1) == 0)
				return (NULL);
		}
		else
			offset = (size_t)(match - b->str) + 1;
	}
	return (b);
}
