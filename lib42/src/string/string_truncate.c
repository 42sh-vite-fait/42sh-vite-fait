/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_truncate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 16:30:58 by djean             #+#    #+#             */
/*   Updated: 2016/10/18 10:33:56 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_42.h"

t_string	*string_truncate(t_string *s, size_t n)
{
	if (n > s->len)
		return (NULL);
	s->len = n;
	s->str[s->len] = '\0';
	return (s);
}
