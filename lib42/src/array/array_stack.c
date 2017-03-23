/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 16:31:26 by djean             #+#    #+#             */
/*   Updated: 2016/10/17 16:32:19 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_42.h"

t_array		*array_push(t_array *a, const void *e)
{
	if (array_reserve(a, 1) == NULL)
		return (NULL);
	a->len += 1;
	ft_memcpy(array_get_at(a, a->len - 1), e, a->elem_size);
	return (a);
}

t_array		*array_pop(t_array *a, void *old)
{
	if (a->len == 0)
		return (NULL);
	if (array_remove_at(a, a->len - 1, old) == NULL)
		return (NULL);
	return (a);
}
