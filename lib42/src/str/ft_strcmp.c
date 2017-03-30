/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:51:26 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 16:51:46 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "string_42.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	s1len;
	size_t	s2len;
	size_t	min;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	min = FT_MIN(s1len + 1, s2len + 1);
	return (ft_memcmp(s1, s2, min));
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	s1len;
	size_t	s2len;
	size_t	min;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	min = FT_MIN(s1len + 1, s2len + 1);
	min = FT_MIN(min, n);
	return (ft_memcmp(s1, s2, min));
}

bool	ft_streq(const char *s1, const char *s2)
{
	return (ft_strcmp(s1, s2) == 0);
}
