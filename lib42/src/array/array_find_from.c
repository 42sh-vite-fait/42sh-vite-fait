/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_nfind.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 13:33:47 by tvallee           #+#    #+#             */
/*   Updated: 2016/11/15 15:43:24 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_42.h"

void	*array_find_from(t_array set, size_t n,
		int (match)(const void *elem, const void *param), const void *param)
{
	void	*elem;

	while ((elem = array_get_at(&set, n++)) != NULL)
		if (match(elem, param))
			return (elem);
	return (NULL);
}

void	*array_find(t_array set,
		int (match)(const void *elem, const void *param), const void *param)
{
	return (array_find_from(set, 0, match, param));
}
