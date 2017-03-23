/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 12:14:45 by djean             #+#    #+#             */
/*   Updated: 2016/10/09 20:05:02 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_42.h"

static void		init_skip_table(const char *pattern, size_t len, size_t *table)
{
	size_t		i;

	i = 0;
	while (i < ASCII_TABLE_LEN)
	{
		table[i] = len;
		++i;
	}
	i = 0;
	while (i < len)
	{
		table[(size_t)pattern[i]] = len - i - 1;
		++i;
	}
}

char			*ft_strstr(const char *big, const char *little)
{
	return (ft_strnstr(big, little, ft_strlen(big)));
}

char			*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		skip_table[ASCII_TABLE_LEN];
	size_t		little_len;
	size_t		skip;
	size_t		i;

	if (*little == '\0')
		return ((char *)(uintptr_t)big);
	little_len = ft_strlen(little);
	init_skip_table(little, little_len, skip_table);
	if (little_len <= len)
	{
		skip = 0;
		while (skip <= len - little_len)
		{
			i = little_len - 1;
			while (little[i] == big[skip + i])
			{
				if (i == 0)
					return ((char *)(uintptr_t)(big + skip));
				--i;
			}
			skip += skip_table[(size_t)big[skip + i]];
		}
	}
	return (NULL);
}
