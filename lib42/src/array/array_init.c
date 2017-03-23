/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 16:31:25 by djean             #+#    #+#             */
/*   Updated: 2016/10/18 16:55:27 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_42.h"

t_array		*array_init(t_array *a, size_t elem_size)
{
	return (array_init_with_capacity(a, elem_size, ARRAY_INIT_SIZE));
}

t_array		*array_init_with_capacity(t_array *a, size_t elem_size, size_t cap)
{
	if (elem_size == 0)
		return (NULL);
	a->capacity = cap;
	if (a->capacity < ARRAY_INIT_SIZE)
		a->capacity = ARRAY_INIT_SIZE;
	else if (!IS_POWER_OF_2(a->capacity))
		a->capacity = next_power_of_2(a->capacity);
	a->len = 0;
	a->elem_size = elem_size;
	if ((a->data = malloc(a->elem_size * a->capacity)) == NULL)
		return (NULL);
	return (a);
}

void		array_shutdown(t_array *a)
{
	free(a->data);
}
