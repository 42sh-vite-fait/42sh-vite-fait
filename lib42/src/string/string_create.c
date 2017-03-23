/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 16:30:57 by djean             #+#    #+#             */
/*   Updated: 2016/10/18 10:23:04 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_42.h"

t_string	*string_create(void)
{
	return (string_create_with_capacity(STRING_INIT_SIZE - 1));
}

t_string	*string_create_with_capacity(size_t capacity)
{
	t_string	*s;

	s = malloc(sizeof(t_string));
	if (s == NULL)
		return (NULL);
	if (string_init_with_capacity(s, capacity) == NULL)
		return (NULL);
	return (s);
}

void		string_destroy(t_string *s)
{
	free(s->str);
	free(s);
}
