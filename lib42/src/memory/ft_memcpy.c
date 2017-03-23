/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 15:50:37 by djean             #+#    #+#             */
/*   Updated: 2016/10/01 15:53:07 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_42.h"

inline static void	align_word(unsigned char **dest, const unsigned char **src,
		size_t *n)
{
	while (*n > 0 && (uintptr_t)(*dest) % MEM_WORD_LEN != 0)
	{
		(*dest)[0] = (*src)[0];
		*dest += 1;
		*src += 1;
		*n -= 1;
	}
}

inline static void	copy_blocks(unsigned long **dest, const unsigned long **src,
		size_t *n)
{
	while (*n >= MEM_BLOCK_SIZE)
	{
		(*dest)[0] = (*src)[0];
		(*dest)[1] = (*src)[1];
		(*dest)[2] = (*src)[2];
		(*dest)[3] = (*src)[3];
		(*dest)[4] = (*src)[4];
		(*dest)[5] = (*src)[5];
		(*dest)[6] = (*src)[6];
		(*dest)[7] = (*src)[7];
		*dest += 8;
		*src += 8;
		*n -= MEM_BLOCK_SIZE;
	}
}

inline static void	copy_words(unsigned long **dest, const unsigned long **src,
		size_t *n)
{
	while (*n >= MEM_WORD_LEN)
	{
		(*dest)[0] = (*src)[0];
		*dest += 1;
		*src += 1;
		*n -= MEM_WORD_LEN;
	}
}

inline static void	copy_bytes(unsigned char **dest, const unsigned char **src,
		size_t *n)
{
	while (*n > 0)
	{
		(*dest)[0] = (*src)[0];
		*dest += 1;
		*src += 1;
		*n -= 1;
	}
}

void				*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*orig;

	orig = dest;
	if (n > 0)
	{
		align_word((unsigned char**)&dest, (const unsigned char**)&src, &n);
		copy_blocks((unsigned long**)&dest, (const unsigned long**)&src, &n);
		copy_words((unsigned long**)&dest, (const unsigned long**)&src, &n);
		copy_bytes((unsigned char**)&dest, (const unsigned char**)&src, &n);
	}
	return (orig);
}
