#include <stdio.h> // delete

#include "typedefs_42.h"
#include "string_42.h"
#include "buffer_42.h"
#include "misc.h"

t_buffer		*buffer_escape(t_buffer *b, int c)
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

t_buffer		*buffer_unescape(t_buffer *b, int c)
{
	char		pattern[3];
	char		*match;
	size_t		offset;

	offset = 0;
	pattern[0] = '\\';
	pattern[1] = (char)c;
	pattern[2] = '\0';
	while ((match = ft_strstr(b->str + offset, pattern)) != NULL)
	{
		if (rev_count_dup(match, b->str + offset, '\\') & 1)
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
