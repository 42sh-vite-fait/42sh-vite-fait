/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbuffer_reserve_shrink.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 16:12:42 by crenault          #+#    #+#             */
/*   Updated: 2016/10/25 15:16:14 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cbuffer_42.h"
#include "memory_42.h"

inline static void	copy_data(t_cbuffer const *b, char *new_data)
{
	size_t		rest;

	if (b->start > b->end)
	{
		rest = b->capacity - b->start;
		ft_memcpy(new_data, (char*)b->data + (b->start * b->elem_size),
					rest * b->elem_size);
		ft_memcpy(new_data + (rest * b->elem_size), b->data,
					(b->len - rest) * b->elem_size);
	}
	else
	{
		ft_memcpy(new_data, (char*)b->data + (b->start * b->elem_size),
					b->len * b->elem_size);
	}
}

t_cbuffer			*cbuffer_reserve(t_cbuffer *b, size_t additional)
{
	char	*new_data;

	if (b->capacity - b->len < additional)
	{
		if ((new_data = malloc((b->len + additional) * b->elem_size)) == NULL)
			return (NULL);
		copy_data(b, new_data);
		free(b->data);
		b->data = new_data;
		b->start = 0;
		b->end = (b->len == 0) ? 0 : (b->len - 1);
		b->capacity = b->len + additional;
	}
	return (b);
}

t_cbuffer			*cbuffer_shrink_to_fit(t_cbuffer *b)
{
	size_t		new_capacity;
	char		*new_data;

	if (b->len != b->capacity || (b->len == 0 && b->capacity != 1))
	{
		new_capacity = b->len == 0 ? 1 : b->len;
		if ((new_data = malloc(new_capacity * b->elem_size)) == NULL)
			return (NULL);
		copy_data(b, new_data);
		free(b->data);
		b->data = new_data;
		b->start = 0;
		b->end = b->len == 0 ? 0 : b->len - 1;
		b->capacity = new_capacity;
	}
	return (b);
}
