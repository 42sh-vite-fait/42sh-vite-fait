/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 15:53:40 by djean             #+#    #+#             */
/*   Updated: 2016/10/01 15:54:13 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_42.h"

inline static void	align_word(const unsigned char **s1,
		const unsigned char **s2, size_t *n)
{
	while (*n > 0 && (uintptr_t)(*s1) % MEM_WORD_LEN != 0)
	{
		if (**s1 != **s2)
			break ;
		*s1 += 1;
		*s2 += 1;
		*n -= 1;
	}
}

inline static void	cmp_blocks(const unsigned long **s1,
		const unsigned long **s2, size_t *n)
{
	while (*n >= MEM_BLOCK_SIZE)
	{
		if ((*s1)[0] != (*s2)[0]
				|| (*s1)[1] != (*s2)[1]
				|| (*s1)[2] != (*s2)[2]
				|| (*s1)[3] != (*s2)[3]
				|| (*s1)[4] != (*s2)[4]
				|| (*s1)[5] != (*s2)[5]
				|| (*s1)[6] != (*s2)[6]
				|| (*s1)[7] != (*s2)[7])
			break ;
		*s1 += 8;
		*s2 += 8;
		*n -= MEM_BLOCK_SIZE;
	}
}

inline static void	cmp_words(const unsigned long **s1,
		const unsigned long **s2, size_t *n)
{
	while (*n >= MEM_WORD_LEN)
	{
		if (**s1 != **s2)
			break ;
		*s1 += 1;
		*s2 += 1;
		*n -= MEM_WORD_LEN;
	}
}

inline static void	cmp_bytes(const unsigned char **s1,
		const unsigned char **s2, size_t *n)
{
	while (*n > 0)
	{
		if (**s1 != **s2)
			break ;
		*s1 += 1;
		*s2 += 1;
		*n -= 1;
	}
}

int					ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int	res;

	res = 0;
	if (n > 0)
	{
		align_word((const unsigned char**)&s1, (const unsigned char**)&s2, &n);
		cmp_blocks((const unsigned long**)&s1, (const unsigned long**)&s2, &n);
		cmp_words((const unsigned long**)&s1, (const unsigned long**)&s2, &n);
		cmp_bytes((const unsigned char**)&s1, (const unsigned char**)&s2, &n);
		if (n > 0)
			res = (int)(*(const unsigned char*)s1 - *(const unsigned char*)s2);
	}
	return (res);
}
