#include "ft_printf.h"

int	conv_wcs(t_string *pb, t_format *fmt, va_list ap)
{
	char	*arg;
	wchar_t	*wcs;
	size_t	arglenmax;
	size_t	wlen;

	if ((wcs = va_arg(ap, wchar_t*)) == NULL)
		wcs = L"(null)";
	arglenmax = ft_wcslen(wcs) * sizeof(wchar_t) + 1;
	if ((arg = (char*)malloc(arglenmax)) == 0)
		exit_printf(4);
	wlen = (fmt->prec < 0) ? arglenmax : (size_t)fmt->prec;
	if ((wlen = ft_wcstombs(arg, wcs, wlen)) == (size_t)-1)
		return (-1);
	if (fmt->f_minus == 0)
		str_formatting(pb, fmt, wlen);
	string_ncat(pb, arg, wlen);
	if (fmt->min_width > 0 && fmt->f_minus == 1)
		str_formatting(pb, fmt, wlen);
	free(arg);
	return (1);
}
