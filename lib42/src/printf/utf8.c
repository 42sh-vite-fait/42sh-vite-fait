#include "ft_printf.h"

/*
** UTF-8 range forbidden: [https://tools.ietf.org/html/rfc3629]
**		Surrogate pairs -> U+D800 <=> U+DFFF
** 		Max accessible -> U+10FFFF
** Futur:
** 5 bytes sequences -> if ((unicode & 0xC0000000) == 0)
** 6 bytes sequences -> if ((unicode & 0x80000000) == 0)
*/

int		ft_wctomb(char *s, wchar_t wchar)
{
	if (wchar < 0)
		return (-1);
	if (wchar >= 0xD800 && wchar <= 0xDFFF)
		return (-1);
	if (wchar > 0x10FFFF)
		return (-1);
	if ((wchar >> 7) == 0)
	{
		s[0] = (char)wchar;
		return (1);
	}
	if ((wchar >> 11) == 0)
		return (conv_to_utf8(2, wchar, s));
	if ((wchar >> 16) == 0)
		return (conv_to_utf8(3, wchar, s));
	if ((wchar >> 21) == 0)
		return (conv_to_utf8(4, wchar, s));
	return (-1);
}

size_t	ft_wcstombs(char *s, wchar_t *pwcs, size_t n)
{
	char	tmp[MB_LEN_MAX];
	size_t	offset;
	int		i;

	offset = 0;
	while (*pwcs != L'\0' && n != 0)
	{
		if ((i = ft_wctomb(tmp, *pwcs)) == -1)
			return ((size_t)-1);
		if ((size_t)i > n)
			break ;
		ft_memcpy(s + offset, tmp, (size_t)i);
		offset += (size_t)i;
		++pwcs;
		n -= (size_t)i;
	}
	if (n > 0)
		s[offset] = '\0';
	return (offset);
}

size_t	ft_wcslen(const wchar_t *s)
{
	size_t	i;

	i = 0;
	while (s[i] != L'\0')
		i += 1;
	return (i);
}

int		conv_to_utf8(int wbytes, wchar_t wchar, char *s)
{
	if (wbytes == 2)
	{
		s[1] = 0x80 | (char)(wchar & 0x3F);
		s[0] = 0xC0 | (char)(wchar >> 6 & 0x1F);
	}
	else if (wbytes == 3)
	{
		s[2] = 0x80 | (char)(wchar & 0x3F);
		s[1] = 0x80 | (char)(wchar >> 6 & 0x3F);
		s[0] = 0xE0 | (char)(wchar >> 12 & 0x0F);
	}
	else if (wbytes == 4)
	{
		s[3] = 0x80 | (char)(wchar & 0x3F);
		s[2] = 0x80 | (char)(wchar >> 6 & 0x3F);
		s[1] = 0x80 | (char)(wchar >> 12 & 0x3F);
		s[0] = 0xF0 | (char)(wchar >> 18 & 0x07);
	}
	return (wbytes);
}
