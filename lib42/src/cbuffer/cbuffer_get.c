/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbuffer_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 19:51:28 by crenault          #+#    #+#             */
/*   Updated: 2016/10/10 19:48:20 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "structs_42.h"
#include "typedefs_42.h"
#include "cbuffer_42.h"

void		*cbuffer_get_at(const t_cbuffer *buffer, size_t i)
{
	if (i >= buffer->len || buffer->len == 0)
		return (NULL);
	if (buffer->start + i >= buffer->capacity)
		return (CBUFFER_AT_INDEX(buffer, buffer->start + i - buffer->capacity));
	return (CBUFFER_AT_INDEX(buffer, buffer->start + i));
}

void		*cbuffer_get_front(const t_cbuffer *buffer)
{
	if (buffer->len == 0)
		return (NULL);
	return (CBUFFER_AT_INDEX(buffer, buffer->start));
}

void		*cbuffer_get_back(const t_cbuffer *buffer)
{
	if (buffer->len == 0)
		return (NULL);
	return (CBUFFER_AT_INDEX(buffer, buffer->end));
}
