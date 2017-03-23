/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_shrink_to_fit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 18:33:05 by crenault          #+#    #+#             */
/*   Updated: 2016/10/18 12:01:13 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_42.h"

t_array		*array_shrink_to_fit(t_array *a)
{
	size_t	capacity;

	if (a->len != a->capacity)
	{
		if (a->len <= ARRAY_INIT_SIZE)
			capacity = ARRAY_INIT_SIZE;
		else
			capacity = next_power_of_2(a->len);
		if (capacity < a->capacity)
		{
			a->capacity = capacity;
			a->data = ft_realloc(a->data, a->capacity * a->elem_size,
								a->len * a->elem_size);
			if (a->data == NULL)
				return (NULL);
		}
	}
	return (a);
}
