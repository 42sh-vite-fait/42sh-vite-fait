/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:22:42 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:22:46 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "string_42.h"
#include "misc.h"

const char	*str_token(t_string *next_line, const char *input, char sep)
{
	ssize_t	len;

	len = ft_strchrpos(input, sep);
	if (len >= 0)
	{
		fatal_malloc(string_init_ndup(next_line, input, len));
		input += len + 1;
	}
	else
	{
		len = ft_strlen(input) & _POSIX_SSIZE_MAX;
		if (len == 0)
			return (NULL);
		fatal_malloc(string_init_ndup(next_line, input, len));
		input += len;
	}
	return (input);
}
