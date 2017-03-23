/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_truncate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 16:30:58 by djean             #+#    #+#             */
/*   Updated: 2016/10/18 14:06:17 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_42.h"

t_array		*array_truncate(t_array *a, size_t n)
{
	if (n > a->len)
		return (NULL);
	a->len = n;
	return (a);
}
