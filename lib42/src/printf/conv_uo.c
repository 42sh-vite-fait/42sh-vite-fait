/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_uo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:51:26 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 16:51:46 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	formatting_o(t_string *pb, t_format *fmt, char *arg, size_t arglen)
{
	int_format_intro(fmt, arg, &arglen);
	if (fmt->f_minus == 0)
		int_padding(pb, fmt, (fmt->f_sharp) ? arglen + 1 : arglen, arg[0]);
	if (fmt->f_sharp && (ft_strcmp("0", arg) || fmt->prec == 0))
		string_ncat(pb, "0", 1);
	int_precision(pb, fmt, (fmt->f_sharp) ? arglen + 1 : arglen);
	string_ncat(pb, arg, arglen);
	if (fmt->f_minus == 1)
		int_padding(pb, fmt, (fmt->f_sharp) ? arglen + 1 : arglen, arg[0]);
	return (1);
}

static int	formatting_u(t_string *pb, t_format *fmt, char *arg, size_t arglen)
{
	fmt->f_sharp = 0;
	fmt->f_space = 0;
	fmt->f_plus = 0;
	return (formatting_o(pb, fmt, arg, arglen));
}

int			conv_u(t_string *pb, t_format *fmt, va_list ap)
{
	char	*arg;

	if (fmt->len_mod == '\0')
		arg = ft_utoa_base(va_arg(ap, unsigned), 10);
	else if (fmt->len_mod == 'H')
		arg = ft_utoa_base((unsigned char)va_arg(ap, unsigned), 10);
	else if (fmt->len_mod == 'h')
		arg = ft_utoa_base((unsigned short)va_arg(ap, unsigned), 10);
	else
		arg = ft_utoa_base(va_arg(ap, unsigned long), 10);
	if (!arg)
		exit_printf(6);
	formatting_u(pb, fmt, arg, ft_strlen(arg));
	free(arg);
	return (1);
}

int			conv_o(t_string *pb, t_format *fmt, va_list ap)
{
	char	*arg;

	if (fmt->len_mod == '\0')
		arg = ft_utoa_base(va_arg(ap, unsigned), 8);
	else if (fmt->len_mod == 'H')
		arg = ft_utoa_base((unsigned char)va_arg(ap, unsigned), 8);
	else if (fmt->len_mod == 'h')
		arg = ft_utoa_base((unsigned short)va_arg(ap, unsigned), 8);
	else
		arg = ft_utoa_base(va_arg(ap, unsigned long), 8);
	if (!arg)
		exit_printf(7);
	formatting_o(pb, fmt, arg, ft_strlen(arg));
	free(arg);
	return (1);
}
