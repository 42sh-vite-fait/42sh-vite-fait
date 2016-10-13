#include <stdbool.h>
#include "typedefs_42.h"
#include "string_42.h"
#include "buffer_42.h"
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

t_buffer		*buffer_escape_chars(t_buffer *b, int c)
{
	char		*match;
	size_t		offset;

	offset = 0;
	while ((match = ft_strchr(b->str + offset, c)) != NULL)
	{
		offset = (size_t)(match - b->str);
		if (buffer_insert(b, offset, "\\", 1) == NULL)
			return (NULL);
		offset += 2;
	}
	return (b);
}

t_buffer		*buffer_unescape_chars(t_buffer *b, int c)
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
			if (buffer_remove(b, offset, 1) == 0)
				return (NULL);
		}
		else
			offset = (size_t)(match - b->str) + 1;
	}
	return (b);
}
