/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbuffer_push.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 16:12:42 by crenault          #+#    #+#             */
/*   Updated: 2016/10/10 19:48:29 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_42.h"
#include "typedefs_42.h"
#include "cbuffer_42.h"
#include "memory_42.h"

void					cbuffer_push_back(t_cbuffer *b, const void *elem)
{
	if (b->len == 0)
	{
		b->len += 1;
	}
	else if (b->len == b->capacity)
	{
		b->end = CBUFFER_MOVE_FORWARD(b->capacity, b->end);
		b->start = CBUFFER_MOVE_FORWARD(b->capacity, b->start);
		if (b->delete_func != NULL)
		{
			(*b->delete_func)(CBUFFER_AT_INDEX(b, b->end));
		}
	}
	else
	{
		b->len += 1;
		b->end = CBUFFER_MOVE_FORWARD(b->capacity, b->end);
	}
	ft_memcpy(CBUFFER_AT_INDEX(b, b->end), elem, b->elem_size);
}

void					cbuffer_push_front(t_cbuffer *b, const void *elem)
{
	if (b->len == 0)
	{
		b->len += 1;
	}
	else if (b->len == b->capacity)
	{
		b->start = CBUFFER_MOVE_BACKWARD(b->capacity, b->start);
		b->end = CBUFFER_MOVE_BACKWARD(b->capacity, b->end);
		if (b->delete_func != NULL)
		{
			(*b->delete_func)(CBUFFER_AT_INDEX(b, b->start));
		}
	}
	else
	{
		b->len += 1;
		b->start = CBUFFER_MOVE_BACKWARD(b->capacity, b->start);
	}
	ft_memcpy(CBUFFER_AT_INDEX(b, b->start), elem, b->elem_size);
}
