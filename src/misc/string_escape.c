/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_escape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:22:42 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:23:29 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_string	*string_escape_chars(t_string *s, int c)
{
	ssize_t		match_pos;
	size_t		offset;

	offset = 0;
	while ((match_pos = ft_strchrpos(s->str + offset, c)) != -1)
	{
		offset += (size_t)match_pos;
		fatal_malloc(string_insert(s, offset, "\\", 1));
		offset += 2;
	}
	return (s);
}

t_string	*string_unescape_chars(t_string *s, int c)
{
	static char		pattern[3] = {'\\', '\0', '\0'};
	char			*match;
	size_t			offset;

	offset = 0;
	pattern[1] = (char)c;
	while ((match = ft_strstr(s->str + offset, pattern)) != NULL)
	{
		if (is_escaped(match + 1, s->str + offset))
		{
			offset = (size_t)(match - s->str);
			if (string_remove(s, offset, 1) == 0)
				return (NULL);
		}
		else
			offset = (size_t)(match - s->str) + 1;
	}
	return (s);
}
