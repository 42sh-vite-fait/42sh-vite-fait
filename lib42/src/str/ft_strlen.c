/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:51:26 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 16:54:37 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_42.h"

size_t	ft_strlen(const char *s)
{
	return ((uintptr_t)(ft_memchr(s, (int)'\0', ~0ULL)) - (uintptr_t)s);
}

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	void	*result;

	if ((result = ft_memchr(s, (int)'\0', maxlen)))
		return ((uintptr_t)result - (uintptr_t)s);
	return (maxlen);
}
