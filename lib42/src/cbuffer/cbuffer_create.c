/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbuffer_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 16:01:15 by crenault          #+#    #+#             */
/*   Updated: 2016/10/08 18:28:07 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "structs_42.h"
#include "typedefs_42.h"
#include "cbuffer_42.h"

t_cbuffer	*cbuffer_create(size_t capacity, size_t elem_size,
							void (*delete_func)(void *))
{
	t_cbuffer	*buffer;

	buffer = malloc(sizeof(t_cbuffer));
	if (buffer == NULL)
		return (NULL);
	if ((cbuffer_init(buffer, capacity, elem_size, delete_func)) == NULL)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

void		cbuffer_destroy(t_cbuffer *buffer)
{
	cbuffer_shutdown(buffer);
	free(buffer);
}
