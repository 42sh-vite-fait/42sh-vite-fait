/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:51:37 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 16:55:29 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_42.h"

/*
** Append the char 'c', 'n' times, to the buffer
*/

t_string	*string_set(t_string *s, int c, size_t n)
{
	if (string_reserve(s, n + 1) == NULL)
		return (NULL);
	ft_memset(s->str + s->len, c, n);
	s->len += n;
	s->str[s->len] = 0;
	return (s);
}
