/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 17:34:22 by djean             #+#    #+#             */
/*   Updated: 2016/10/11 23:36:32 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib_42.h"

void	*ft_realloc(void *ptr, size_t size, size_t oldsize)
{
	void	*p;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if ((p = malloc(size)) == NULL)
		return (NULL);
	ft_memcpy(p, ptr, oldsize);
	free(ptr);
	return (p);
}
