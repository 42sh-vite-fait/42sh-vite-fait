/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 16:30:57 by djean             #+#    #+#             */
/*   Updated: 2016/10/18 10:50:08 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_42.h"

t_string	*string_init(t_string *s)
{
	return (string_init_with_capacity(s, STRING_INIT_SIZE - 1));
}

t_string	*string_init_with_capacity(t_string *s, size_t capacity)
{
	s->capacity = capacity + 1;
	if (s->capacity < STRING_INIT_SIZE)
		s->capacity = STRING_INIT_SIZE;
	else if (!IS_POWER_OF_2(s->capacity))
		s->capacity = next_power_of_2(s->capacity);
	if ((s->str = malloc(s->capacity)) == NULL)
		return (NULL);
	s->len = 0;
	s->str[0] = '\0';
	return (s);
}

void		string_shutdown(t_string *s)
{
	free(s->str);
}
