/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 15:49:43 by djean             #+#    #+#             */
/*   Updated: 2016/10/01 15:50:10 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_42.h"

/*
** Set the value 'c' to the first 'len' bytes in the memory space
** pointed to by 'b'.
*/

inline static void	align_word(unsigned char **p, unsigned char c, size_t *len)
{
	while (*len > 0 && (((uintptr_t)(*p) % MEM_WORD_LEN) != 0))
	{
		(*p)[0] = c;
		*p += 1;
		*len -= 1;
	}
}

inline static void	setblocks(unsigned long **p, unsigned long cccc,
								size_t *len)
{
	while (*len >= MEM_BLOCK_SIZE)
	{
		(*p)[0] = cccc;
		(*p)[1] = cccc;
		(*p)[2] = cccc;
		(*p)[3] = cccc;
		(*p)[4] = cccc;
		(*p)[5] = cccc;
		(*p)[6] = cccc;
		(*p)[7] = cccc;
		*p += 8;
		*len -= MEM_BLOCK_SIZE;
	}
}

inline static void	setwords(unsigned long **p, unsigned long cccc, size_t *len)
{
	while (*len >= MEM_WORD_LEN)
	{
		(*p)[0] = cccc;
		*p += 1;
		*len -= MEM_WORD_LEN;
	}
}

inline static void	setbytes(unsigned char **p, unsigned char c, size_t *len)
{
	while (*len > 0)
	{
		(*p)[0] = c;
		*p += 1;
		*len -= 1;
	}
}

void				*ft_memset(void *b, int c, size_t len)
{
	unsigned long int	cccc;

	cccc = (unsigned char)c;
	cccc |= cccc << 24 | cccc << 16 | cccc << 8;
	cccc |= cccc << 32;
	align_word((unsigned char**)&b, (unsigned char)c, &len);
	setblocks((unsigned long**)&b, cccc, &len);
	setwords((unsigned long**)&b, cccc, &len);
	setbytes((unsigned char**)&b, (unsigned char)c, &len);
	return (b);
}
