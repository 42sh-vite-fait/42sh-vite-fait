/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 11:25:01 by djean             #+#    #+#             */
/*   Updated: 2016/11/22 16:27:17 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pool_42.h"

t_pool	*pool_init(t_pool *p, size_t elem_size)
{
	if (elem_size == 0)
		return (NULL);
	p->elem_size = ROUND_UP_8(elem_size);
	p->chunk_capacity = CHUNK_CAPACITY(p->elem_size);
	p->chunks_list = NULL;
	p->free_list = NULL;
	if (pool_add_chunk(p) == NULL)
		return (NULL);
	return (p);
}

void	pool_shutdown(t_pool *p)
{
	void	*ptr;

	while (p->chunks_list)
	{
		ptr = p->chunks_list;
		p->chunks_list = p->chunks_list->next;
		free(ptr);
	}
	p->chunks_list = NULL;
	p->free_list = NULL;
}
