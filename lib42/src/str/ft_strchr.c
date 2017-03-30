/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:51:26 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 16:54:23 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_42.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *)((uintptr_t)s + len));
	return (ft_memchr(s, c, len));
}

ssize_t	ft_strchrpos(const char *s, int c)
{
	char	*p;

	p = ft_strchr(s, c);
	if (p == NULL)
		return (-1);
	return ((ssize_t)(p - s));
}

char	*ft_strnchr(const char *s, int c, size_t n)
{
	size_t	len;

	len = ft_strlen(s) + 1;
	if (len > n)
		len = n;
	return (ft_memchr(s, c, len));
}

ssize_t	ft_strnchrpos(const char *s, int c, size_t n)
{
	char	*p;

	p = ft_strnchr(s, c, n);
	if (p == NULL)
		return (-1);
	return ((ssize_t)(p - s));
}
