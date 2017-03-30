/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ato_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:51:26 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 16:51:46 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib_42.h"
#include "ctype_42.h"

inline static int			get_char_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else
		return (-1);
}

inline static const char	*skip_blank(const char *str)
{
	while (*str && FT_ISBLANK(*str))
		str += 1;
	return (str);
}

size_t						ft_atou_base(const char *str, unsigned base)
{
	int		char_val;
	size_t	ret;

	ret = 0;
	str = skip_blank(str);
	char_val = get_char_value(*str);
	while (*str && char_val != -1 && (unsigned)char_val < base)
	{
		ret = ret * base + (size_t)char_val;
		str += 1;
		char_val = get_char_value(*str);
	}
	return (ret);
}

ssize_t						ft_atoi_base(const char *str, unsigned base)
{
	int			char_val;
	ssize_t		ret;
	int			sign;

	ret = 0;
	str = skip_blank(str);
	if (*str == '-')
	{
		sign = -1;
		str += 1;
	}
	else
		sign = 1;
	char_val = get_char_value(*str);
	while (*str && char_val != -1 && (unsigned)char_val < base)
	{
		ret = ret * base + char_val * sign;
		str += 1;
		char_val = get_char_value(*str);
	}
	return (ret);
}

size_t						ft_atou(const char *str)
{
	if (!ft_strncmp(str, "0x", 2))
		return (ft_atou_base(str + 2, 16));
	else if (!ft_strncmp(str, "0b", 2))
		return (ft_atou_base(str + 2, 2));
	else if (!ft_strncmp(str, "0", 1))
		return (ft_atou_base(str + 1, 8));
	else
		return (ft_atou_base(str, 10));
}
