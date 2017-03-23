/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 11:25:03 by djean             #+#    #+#             */
/*   Updated: 2016/11/22 12:06:12 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pool_42.h"

t_pool	*pool_create(size_t elem_size)
{
	t_pool	*p;

	p = malloc(sizeof(t_pool));
	if (p != NULL)
	{
		if (pool_init(p, elem_size) == NULL)
		{
			free(p);
			p = NULL;
		}
	}
	return (p);
}

void	pool_destroy(t_pool *p)
{
	pool_shutdown(p);
	free(p);
}
