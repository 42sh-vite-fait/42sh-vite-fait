/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_shrink_to_fit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 18:33:05 by crenault          #+#    #+#             */
/*   Updated: 2016/10/17 15:02:13 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_42.h"

t_string	*string_shrink_to_fit(t_string *s)
{
	size_t	capacity;

	if (s->len + 1 != s->capacity)
	{
		if (s->len + 1 <= STRING_INIT_SIZE)
			capacity = STRING_INIT_SIZE;
		else
			capacity = next_power_of_2(s->len + 1);
		if (capacity < s->capacity)
		{
			s->capacity = capacity;
			s->str = ft_realloc(s->str, capacity, s->len + 1);
			if (s->str == NULL)
				return (NULL);
		}
	}
	return (s);
}
