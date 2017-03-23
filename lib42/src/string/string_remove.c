/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 16:30:57 by djean             #+#    #+#             */
/*   Updated: 2016/10/15 15:35:29 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_42.h"

size_t		string_remove(t_string *s, size_t pos, size_t n)
{
	size_t	removed;

	if (pos >= s->len)
		return (0);
	if (pos + n >= s->len)
	{
		removed = s->len - pos;
		s->len = pos;
	}
	else
	{
		removed = n;
		ft_memmove(s->str + pos, s->str + pos + n, s->len - (pos + n));
		s->len -= n;
	}
	s->str[s->len] = '\0';
	return (removed);
}

ssize_t		string_remove_back(t_string *s, size_t n)
{
	if (n > s->len)
		return (-1);
	s->len -= n;
	s->str[s->len] = '\0';
	return ((ssize_t)s->len);
}

ssize_t		string_remove_back_chr(t_string *s, int c)
{
	ssize_t	pos;
	size_t	ret;

	pos = ft_strrchrpos(s->str, c);
	if (pos == -1)
		return (-1);
	s->str[pos] = '\0';
	ret = s->len - (size_t)pos;
	s->len = (size_t)pos;
	return ((ssize_t)ret);
}
