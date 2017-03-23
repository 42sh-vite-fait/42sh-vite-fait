/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 15:03:46 by djean             #+#    #+#             */
/*   Updated: 2016/11/05 14:35:54 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_42.h"

/*
** Standard 7.20.3: malloc(0)
** If the size of the space requested is zero,
** the behavior is implementation- deﬁned: either a null pointer is returned,
** or the behavior is as if the size were some nonzero value,
** except that the returned pointer shall not be used to access an object.
*/

void	*ft_memalloc(size_t size)
{
	void	*p;

	if (size == 0 || (p = malloc(size)) == NULL)
		return (NULL);
	ft_memset(p, 0x0, size);
	return (p);
}

void	*malloc_or_die(size_t size)
{
	return (fatal_malloc(malloc(size)));
}
