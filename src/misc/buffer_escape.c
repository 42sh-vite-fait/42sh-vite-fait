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

// TODO rename string_*
t_buffer		*buffer_escape_chars(t_buffer *b, int c)
{
	int			match_pos;
	size_t		offset;

	offset = 0;
	// TODO count numbers of c to resize
	while ((match_pos = ft_strchrpos(b->str + offset, c)) != -1)
	{
		offset = (size_t)match_pos + offset; // TODO remove cast
		if (buffer_insert(b, offset, "\\", 1) == NULL)
			return (NULL);
		offset += 2;
	}
	return (b);
}

// TODO rename string_*
t_buffer		*buffer_unescape_chars(t_buffer *b, int c)
{
	static char		pattern[3] = {'\\', '\0', '\0'};
	char			*match;
	size_t			offset;

	offset = 0;
	pattern[1] = (char)c;
	// TODO count numbers of c to resize
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
