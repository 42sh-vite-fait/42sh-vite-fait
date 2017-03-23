/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 15:49:35 by djean             #+#    #+#             */
/*   Updated: 2016/10/01 15:51:54 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_42.h"

/*
** Source: https://graphics.stanford.edu/~seander/bithacks.html#ZeroInWord
** Explication: HIGHBIT_0X01
** 	Les bytes supérieur à 0x80 ou égal à 0 auront leur high bit set à 1.
**	Concernant les bytes set à 0, le wraparround des types unsigned permet
**	au high bit d'être set à 1.
** Explication: HIGHBIT_0X80
**	Tout les bytes sont inversés. Ainsi chaque high bit qui n'était pas déjà
**	set à 1, l'est maintenant. Ceux déjà set à 1 passe à 0.
**	Ensuite on applique le pattern qui permet de ne garder que les bytes ayant
**	un high bit set.
** Status:
**	La première expression nous laisse avec les bytes supérieur à 0x80 et
**	égale à 0 avec un high bit set à 1.
**	La seconde expression nous laisse les bytes inférieur à 0x80 et égale à 0
**	avec un high bit set à 1.
** HAS_ZERO:
**	La macro effectue un AND qui permet de réunir les deux expressions et
**	ainsi de ne garder que les bytes égale à 0 initialement.
** Recherche d'un octet précis:
**	On crée un pattern miroir de l'octet qu'on recherche.
**	On pratique un XOR sur le word avec le pattern miroir. Si l'octet qu'on
**	recherche est présent dans le word alors l'octet sera set à 0.
**	On envoie le résultat à la macro HAS_ZERO, qui nous dira si un octet à 0
**	existe.
** Finale:
**	Si la macro HAS_ZERO nous dit qu'un octet à 0 est présent dans le word,
**	il suffit de boucler sur chaque octet du word pour donner son emplacement.
*/

inline static void	*align_word(const unsigned char **s, unsigned char c,
		size_t *n)
{
	while (*n > 0 && (uintptr_t)(*s) % MEM_WORD_LEN != 0)
	{
		if (*s[0] == c)
			return ((void*)(uintptr_t)(*s));
		*s += 1;
		*n -= 1;
	}
	return (NULL);
}

inline static void	*locate_byte_in_word(const unsigned char **s,
		unsigned char c, size_t *n)
{
	while (*n > 0)
	{
		if (**s == c)
			return ((void*)(uintptr_t)(*s));
		*s += 1;
		*n -= 1;
	}
	return (NULL);
}

inline static void	*search_in_words(const unsigned long **s, unsigned char c,
		size_t *n)
{
	unsigned long	cccc;

	cccc = c;
	cccc |= cccc << 24 | cccc << 16 | cccc << 8;
	cccc |= cccc << 32;
	while (*n >= MEM_WORD_LEN)
	{
		if (HAS_BYTE(**s, cccc))
			return (locate_byte_in_word((const unsigned char**)s, c, n));
		*s += 1;
		*n -= MEM_WORD_LEN;
	}
	return (NULL);
}

void				*ft_memchr(const void *s, int c, size_t n)
{
	void	*ptr;

	ptr = NULL;
	if (n > 0)
	{
		ptr = align_word((const unsigned char**)&s, (unsigned char)c, &n);
		if (ptr != NULL)
			return (ptr);
		ptr = search_in_words((const unsigned long**)&s, (unsigned char)c, &n);
		if (ptr != NULL)
			return (ptr);
		ptr = locate_byte_in_word((const unsigned char**)&s, (unsigned char)c,
				&n);
	}
	return (ptr);
}
