/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:51:26 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 16:51:46 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_printf_internal_safe_write(const char *s, size_t len, int fd)
{
	ssize_t	ret;
	ssize_t	cpy;

	cpy = len;
	while ((ret = write(fd, s, len)) > 0 && (size_t)ret != len)
	{
		if (ret == -1)
			return (-1);
		len -= (size_t)ret;
		s += (size_t)ret;
	}
	return (cpy);
}
