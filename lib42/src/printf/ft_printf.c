#include "ft_printf.h"

/*
** Write output to stdout
*/

ssize_t	ft_printf(const char *format, ...)
{
	va_list	ap;
	ssize_t	ret;

	va_start(ap, format);
	ret = ft_vprintf(format, ap);
	va_end(ap);
	return (ret);
}

ssize_t	ft_vprintf(const char *format, va_list ap)
{
	char	*buf;
	ssize_t	ret;

	if ((ret = ft_printf_core(format, ap, &buf)) < 0)
		return (-1);
	ret = ft_printf_internal_safe_write(buf, (size_t)ret, 1);
	free(buf);
	return (ret);
}
