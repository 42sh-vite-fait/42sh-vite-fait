/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 15:50:54 by djean             #+#    #+#             */
/*   Updated: 2016/10/01 15:52:23 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_42.h"

inline static void	move_page_size(unsigned char **dest,
		const unsigned char **src, size_t *n)
{
	unsigned char	swap[MEM_PAGE_SIZE];

	while (*n >= MEM_PAGE_SIZE)
	{
		(*dest) -= MEM_PAGE_SIZE;
		(*src) -= MEM_PAGE_SIZE;
		ft_memcpy(swap, *src, MEM_PAGE_SIZE);
		ft_memcpy(*dest, swap, MEM_PAGE_SIZE);
		*n -= MEM_PAGE_SIZE;
	}
	(*dest) -= *n;
	(*src) -= *n;
	ft_memcpy(swap, *src, *n);
	ft_memcpy(*dest, swap, *n);
}

void				*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*orig;

	orig = dest;
	if (n == 0 || dest == src)
		return (dest);
	else if (src > dest)
		ft_memcpy(dest, src, n);
	else
	{
		dest = (unsigned char*)dest + n;
		src = (const unsigned char*)src + n;
		move_page_size((unsigned char**)&dest, (const unsigned char**)&src, &n);
	}
	return (orig);
}
