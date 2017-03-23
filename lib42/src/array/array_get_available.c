/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_get_available.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 18:18:15 by crenault          #+#    #+#             */
/*   Updated: 2016/10/18 11:57:28 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_42.h"

void	*array_get_available(t_array *a)
{
	if (array_reserve(a, 1) == NULL)
		return (NULL);
	a->len += 1;
	return (array_get_at(a, a->len - 1));
}
