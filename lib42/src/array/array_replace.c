/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/07 11:02:40 by djean             #+#    #+#             */
/*   Updated: 2016/10/29 14:36:18 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_42.h"

t_array		*array_replace_at(t_array *a, size_t i, const void *e, void *old)
{
	void	*p;

	if (i >= a->len)
		return (NULL);
	if (old != NULL)
	{
		p = array_get_at(a, i);
		ft_memcpy(old, p, a->elem_size);
	}
	array_set_at(a, i, e);
	return (a);
}
