/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:51:26 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 16:51:46 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Dynamically allocate a new string with malloc.
** Set *ret to be a pointer to a buffer sufficiently large to hold
** the formatted strings.
** If sufficient space cannot be allocated, return -1 & set ret to NULL
*/

ssize_t	ft_asprintf(char **ret, const char *format, ...)
{
	ssize_t	res;
	va_list	ap;

	va_start(ap, format);
	res = ft_vasprintf(ret, format, ap);
	va_end(ap);
	return (res);
}

ssize_t	ft_vasprintf(char **ret, const char *format, va_list ap)
{
	ssize_t	res;

	*ret = NULL;
	if ((res = ft_printf_core(format, ap, ret)) < 0)
		*ret = NULL;
	return (res);
}
