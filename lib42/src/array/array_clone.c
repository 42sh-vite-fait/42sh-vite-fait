/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_clone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/07 20:14:18 by djean             #+#    #+#             */
/*   Updated: 2016/10/17 15:10:28 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_42.h"

t_array		*array_clone(t_array *dst, const t_array *src)
{
	if (array_init_with_capacity(dst, src->capacity, src->elem_size) == NULL)
		return (NULL);
	dst->len = src->len;
	ft_memcpy(dst->data, src->data, src->len * src->elem_size);
	return (dst);
}
