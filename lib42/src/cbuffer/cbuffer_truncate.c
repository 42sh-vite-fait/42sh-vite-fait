/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbuffer_truncate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 16:12:42 by crenault          #+#    #+#             */
/*   Updated: 2016/10/25 17:36:27 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cbuffer_42.h"
#include "memory_42.h"

static void		*cbuffer_truncate_from(t_cbuffer *buffer, size_t n,
										void *(*pop_method)(t_cbuffer *))
{
	size_t	to_pop;
	void	*popped;

	if (n > buffer->len)
		return (NULL);
	to_pop = buffer->len - n;
	while (to_pop != 0)
	{
		popped = (*pop_method)(buffer);
		if (buffer->delete_func != NULL)
			buffer->delete_func(popped);
		--to_pop;
	}
	return (buffer);
}

t_cbuffer		*cbuffer_truncate_from_back(t_cbuffer *buffer, size_t n)
{
	return (cbuffer_truncate_from(buffer, n, cbuffer_pop_back));
}

t_cbuffer		*cbuffer_truncate_from_front(t_cbuffer *buffer, size_t n)
{
	return (cbuffer_truncate_from(buffer, n, cbuffer_pop_front));
}
