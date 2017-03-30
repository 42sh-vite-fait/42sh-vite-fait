/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:51:26 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 16:51:46 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	conv_s(t_string *pb, t_format *fmt, va_list ap)
{
	char	*arg;
	size_t	arglen;

	if (fmt->len_mod == 'l')
		return (conv_wcs(pb, fmt, ap));
	arg = va_arg(ap, char*);
	if (arg == NULL)
		arg = "(null)";
	arglen = ft_strlen(arg);
	if (fmt->min_width > 0 && fmt->f_minus == 0)
		str_formatting(pb, fmt, arglen);
	if (fmt->prec > -1 && (size_t)fmt->prec < arglen)
		arglen = (size_t)fmt->prec;
	string_ncat(pb, arg, arglen);
	if (fmt->min_width > 0 && fmt->f_minus == 1)
		str_formatting(pb, fmt, arglen);
	return (1);
}
