/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:51:26 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 16:51:43 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	conv_c(t_string *pb, t_format *fmt, va_list ap)
{
	if (fmt->len_mod == 'l')
		return (conv_wc(pb, fmt, ap));
	fmt->prec = -1;
	if (fmt->min_width > 1 && fmt->f_minus == 0)
		str_formatting(pb, fmt, 1);
	if (fmt->no_conv != 0)
		string_ncat(pb, &fmt->no_conv, 1);
	else
		string_ncat(pb, &(char){(char)va_arg(ap, int)}, 1);
	if (fmt->min_width > 1 && fmt->f_minus == 1)
		str_formatting(pb, fmt, 1);
	return (1);
}
