/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:51:26 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 16:51:46 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	formatting_x(t_string *pb, t_format *fmt, char *arg, size_t arglen)
{
	int_format_intro(fmt, arg, &arglen);
	if (fmt->f_minus == 0 && fmt->f_zero == 0)
		int_padding(pb, fmt, (fmt->f_sharp) ? arglen + 2 : arglen, arg[0]);
	if (fmt->conv == 'p')
		string_ncat(pb, "0x", 2);
	else if (fmt->f_sharp && ft_strcmp("0", arg))
		string_ncat(pb, (fmt->conv == 'X') ? "0X" : "0x", 2);
	if (fmt->f_minus == 0 && fmt->f_zero == 1)
		int_padding(pb, fmt, (fmt->f_sharp) ? arglen + 2 : arglen, arg[0]);
	int_precision(pb, fmt, arglen);
	string_ncat(pb, arg, arglen);
	if (fmt->f_minus == 1)
		int_padding(pb, fmt, (fmt->f_sharp) ? arglen + 2 : arglen, arg[0]);
	return (0);
}

int			conv_x(t_string *pb, t_format *fmt, va_list ap)
{
	char	*arg;

	if (fmt->len_mod == '\0')
		arg = ft_utoa_base(va_arg(ap, unsigned), 16);
	else if (fmt->len_mod == 'H')
		arg = ft_utoa_base((unsigned char)va_arg(ap, unsigned), 16);
	else if (fmt->len_mod == 'h')
		arg = ft_utoa_base((unsigned short)va_arg(ap, unsigned), 16);
	else
		arg = ft_utoa_base(va_arg(ap, unsigned long), 16);
	if (!arg)
		exit_printf(8);
	if (fmt->conv == 'X')
		arg = ft_strtoupper(arg);
	formatting_x(pb, fmt, arg, ft_strlen(arg));
	free(arg);
	return (1);
}

int			conv_p(t_string *pb, t_format *fmt, va_list ap)
{
	char	*arg;

	arg = ft_utoa_base((unsigned long long)va_arg(ap, void*), 16);
	if (!arg)
		exit_printf(9);
	fmt->f_sharp = 1;
	formatting_x(pb, fmt, arg, ft_strlen(arg));
	free(arg);
	return (1);
}
