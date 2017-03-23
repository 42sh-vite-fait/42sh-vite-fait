#include "ft_printf.h"

static size_t	g_bufsize = PRF_BUFSIZ;

static int	tables_dispatch(t_string *b, t_format *fmt, va_list ap)
{
	static char	*spec = "csCSdouxXp%";
	static t_fc	fp[11];
	size_t		i;

	fp[0] = &conv_c;
	fp[1] = &conv_s;
	fp[2] = &conv_wc;
	fp[3] = &conv_wcs;
	fp[4] = &conv_d;
	fp[5] = &conv_o;
	fp[6] = &conv_u;
	fp[7] = &conv_x;
	fp[8] = &conv_x;
	fp[9] = &conv_p;
	fp[10] = &conv_prc;
	i = 0;
	while (spec[i] != fmt->conv)
		++i;
	return (fp[i](b, fmt, ap));
}

static char	*parse_fmt(char *format, t_format *fmt)
{
	if (*format == '\0')
		return (format);
	format = parse_flags(format, fmt);
	format = parse_min_width(format, fmt);
	format = parse_precision(format, fmt);
	format = parse_len_mod(format, fmt);
	if (parse_conv(*format, fmt) == 0)
		return (format);
	return (format + 1);
}

void		ft_printf_init(size_t initsize)
{
	if (initsize > 0)
		g_bufsize = initsize;
}

ssize_t		ft_printf_core(const char *format, va_list ap, char **ret)
{
	t_format	fmt;
	t_string	b;
	char		*pconv;

	string_init_with_capacity(&b, g_bufsize);
	while ((pconv = ft_strchr(format, '%')) != NULL)
	{
		ft_memset(&fmt, 0, sizeof(fmt));
		string_ncat(&b, format, (size_t)(pconv - format));
		format = parse_fmt(pconv + 1, &fmt);
		if (fmt.conv != '\0')
			if (tables_dispatch(&b, &fmt, ap) == -1)
				return (cleanup_buf(&b));
	}
	if (*format != '\0')
		string_ncat(&b, format, ft_strlen(format));
	*ret = b.str;
	return ((ssize_t)b.len);
}
