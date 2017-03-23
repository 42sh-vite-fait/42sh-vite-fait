#include "stdio_42.h"

/*
** Macros définissant l'affichage et pouvant être modifiées:
** BYTE_PER_BLOCK	2 // Ne peut contenir que des multiples de 2
** ASCII_PER_LINE	16
*/

static void	print_char(char c)
{
	write(1, &c, 1);
}

static void	print_hexa_block(const char *addr, size_t nbytes)
{
	size_t			i;
	char			*charset;
	unsigned char	c;

	charset = "0123456789abcdef";
	i = 0;
	while (i < nbytes)
	{
		c = (unsigned char)addr[i++];
		print_char(charset[c / 16]);
		print_char(charset[c % 16]);
		if (i % BYTE_PER_BLOCK == 0)
			print_char(' ');
	}
}

static void	print_ascii_line(const char *addr, size_t nbascii)
{
	unsigned char	c;
	size_t			i;

	i = 0;
	while (i < nbascii)
	{
		c = (unsigned char)addr[i++];
		if (FT_ISPRINT(c))
			print_char(c);
		else
			print_char('.');
	}
}

static void	print_padding(size_t size)
{
	size_t	padding;

	if (size >= ASCII_PER_LINE)
		return ;
	padding = NB_COLUMNS - ((size * 2) + (size / BYTE_PER_BLOCK));
	while (padding--)
		print_char(' ');
}

void		ft_print_memory(const void *addr, size_t size)
{
	char	*p;
	size_t	len;

	p = (char *)addr;
	while (size)
	{
		len = (size >= ASCII_PER_LINE) ? ASCII_PER_LINE : size;
		print_hexa_block(p, len);
		print_padding(size);
		print_ascii_line(p, len);
		print_char('\n');
		p += ASCII_PER_LINE;
		if (size >= ASCII_PER_LINE)
			size -= ASCII_PER_LINE;
		else
			size = 0;
	}
}
