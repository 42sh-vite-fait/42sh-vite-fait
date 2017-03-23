/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_reserve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 19:19:08 by crenault          #+#    #+#             */
/*   Updated: 2016/10/16 16:16:22 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_42.h"
#include "stdlib_42.h"

t_string	*string_reserve(t_string *s, size_t additional)
{
	additional += 1;
	if (s->capacity - s->len < additional)
	{
		if (IS_POWER_OF_2(s->len + additional))
			s->capacity = s->len + additional;
		else
			s->capacity = next_power_of_2(s->len + additional);
		s->str = ft_realloc(s->str, s->capacity, s->len);
		if (s->str == NULL)
			return (NULL);
	}
	return (s);
}
