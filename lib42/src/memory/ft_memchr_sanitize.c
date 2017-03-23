/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 19:15:15 by djean             #+#    #+#             */
/*   Updated: 2016/09/16 13:04:06 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_42.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((const unsigned char*)s)[i] == (unsigned char)c)
			return ((void*)((uintptr_t)s + i));
		++i;
	}
	return (NULL);
}
