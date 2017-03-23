#include "ft_printf.h"

int	conv_wc(t_string *pb, t_format *fmt, va_list ap)
{
	char	arg[MB_LEN_MAX + 1];
	size_t	arglen;
	int		wclen;

	if ((wclen = ft_wctomb(arg, va_arg(ap, wint_t))) == -1)
		return (-1);
	arg[wclen] = '\0';
	if ((arglen = ft_strlen(arg)) == 0)
		++arglen;
	fmt->prec = -1;
	if (fmt->min_width > 1 && fmt->f_minus == 0)
		str_formatting(pb, fmt, arglen);
	string_ncat(pb, arg, arglen);
	if (fmt->min_width > 1 && fmt->f_minus == 1)
		str_formatting(pb, fmt, arglen);
	return (1);
}
