/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:51:26 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 16:51:46 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	formatting_d(t_string *pb, t_format *fmt, char *arg, size_t arglen)
{
	fmt->f_sharp = 0;
	int_format_intro(fmt, arg, &arglen);
	if (fmt->f_zero)
		int_sign(pb, fmt, arg);
	if (fmt->f_minus == 0)
		int_padding(pb, fmt, arglen, arg[0]);
	if (fmt->f_zero == 0)
		int_sign(pb, fmt, arg);
	int_precision(pb, fmt, (FT_ISDIGIT(arg[0])) ? arglen : arglen - 1);
	if (!FT_ISDIGIT(arg[0]))
		string_ncat(pb, arg + 1, arglen - 1);
	else
		string_ncat(pb, arg, arglen);
	if (fmt->f_minus == 1)
		int_padding(pb, fmt, arglen, arg[0]);
	return (1);
}

int			conv_d(t_string *pb, t_format *fmt, va_list ap)
{
	char	*arg;

	if (fmt->len_mod == '\0')
		arg = ft_stoa_base(va_arg(ap, int), 10);
	else if (fmt->len_mod == 'H')
		arg = ft_stoa_base((signed char)va_arg(ap, int), 10);
	else if (fmt->len_mod == 'h')
		arg = ft_stoa_base((short)va_arg(ap, int), 10);
	else
		arg = ft_stoa_base(va_arg(ap, long), 10);
	if (!arg)
		exit_printf(5);
	formatting_d(pb, fmt, arg, ft_strlen(arg));
	free(arg);
	return (1);
}
