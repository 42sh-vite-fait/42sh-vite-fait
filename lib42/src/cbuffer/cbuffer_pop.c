/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbuffer_pop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 16:12:42 by crenault          #+#    #+#             */
/*   Updated: 2016/10/10 19:46:03 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_42.h"
#include "typedefs_42.h"
#include "cbuffer_42.h"

void					*cbuffer_pop_back(t_cbuffer *b)
{
	void	*popped;

	if (b->len > 0)
	{
		popped = CBUFFER_AT_INDEX(b, b->end);
		b->end = CBUFFER_MOVE_BACKWARD(b->capacity, b->end);
		b->len -= 1;
		return (popped);
	}
	return (NULL);
}

void					*cbuffer_pop_front(t_cbuffer *b)
{
	void	*popped;

	if (b->len > 0)
	{
		popped = CBUFFER_AT_INDEX(b, b->start);
		b->start = CBUFFER_MOVE_FORWARD(b->capacity, b->start);
		b->len -= 1;
		return (popped);
	}
	return (NULL);
}
