/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 16:30:57 by djean             #+#    #+#             */
/*   Updated: 2016/10/16 16:20:47 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_42.h"

t_string	*string_insert(t_string *s, size_t pos, const char *str, size_t len)
{
	if (pos > s->len)
		return (NULL);
	if (string_reserve(s, len) == NULL)
		return (NULL);
	ft_memmove(s->str + pos + len, s->str + pos, s->len - pos);
	ft_memcpy(s->str + pos, str, len);
	s->len += len;
	s->str[s->len] = 0;
	return (s);
}
