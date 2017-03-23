#include "ft_printf.h"

char	*parse_flags(char *format, t_format *fmt)
{
	char	c;

	c = *format;
	while (c == '#' || c == '0' || c == '-' || c == ' ' || c == '+')
	{
		if (c == '#')
			fmt->f_sharp = 1;
		else if (c == '0')
			fmt->f_zero = 1;
		else if (c == '-')
			fmt->f_minus = 1;
		else if (c == ' ')
			fmt->f_space = 1;
		else if (c == '+')
			fmt->f_plus = 1;
		c = *++format;
	}
	return (format);
}

char	*parse_min_width(char *format, t_format *fmt)
{
	unsigned	n;

	n = (unsigned)*format;
	while (FT_ISDIGIT(n))
	{
		fmt->min_width = fmt->min_width * 10 + (n - '0');
		n = (unsigned)*++format;
	}
	return (format);
}

char	*parse_precision(char *format, t_format *fmt)
{
	int		res;
	char	n;

	n = *format;
	res = -1;
	if (n == '.')
	{
		n = *++format;
		res = 0;
		while (FT_ISDIGIT(n))
		{
			res = res * 10 + (n - '0');
			n = *++format;
		}
	}
	fmt->prec = res;
	return (format);
}

char	*parse_len_mod(char *format, t_format *fmt)
{
	char	c;

	c = *format;
	if (c != 'h' && c != 'l' && c != 'j' && c != 'z')
		return (format);
	if (c == 'h' && format[1] == 'h')
	{
		fmt->len_mod = 'H';
		format += 2;
	}
	else if (c == 'l' && format[1] == 'l')
	{
		fmt->len_mod = 'L';
		format += 2;
	}
	else
	{
		fmt->len_mod = c;
		format += 1;
	}
	return (format);
}

int		parse_conv(char c, t_format *fmt)
{
	if (c == 'd' || c == 'i')
		fmt->conv = 'd';
	else if (c == 'c' || c == 's' || c == 'S' || c == 'C' || c == '%')
		fmt->conv = c;
	else if (c == 'o' || c == 'u' || c == 'x' || c == 'X' || c == 'p')
		fmt->conv = c;
	else if (c == 'D' || c == 'O' || c == 'U')
	{
		fmt->len_mod = 'L';
		fmt->conv = c | 0x20;
	}
	else
	{
		fmt->conv = 'c';
		fmt->no_conv = c;
	}
	return (fmt->conv != 0);
}
