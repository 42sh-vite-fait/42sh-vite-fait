/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool_chunk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:51:26 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 16:57:25 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pool_42.h"

inline static void	chunk_intern_link(void *ptr, size_t size, size_t count)
{
	void	**next;
	size_t	i;

	next = ptr;
	i = 1;
	while (i < count)
	{
		*next = (unsigned char*)ptr + size;
		ptr = *next;
		next += size / 8;
		++i;
	}
	*next = NULL;
}

t_chunk				*pool_add_chunk(t_pool *p)
{
	t_chunk	*chunk;

	chunk = malloc(MAX_CHUNK_SIZE);
	if (chunk == NULL)
		return (NULL);
	chunk_intern_link(&chunk->head, p->elem_size, p->chunk_capacity);
	p->free_list = CHUNK_HEAD(chunk);
	chunk->next = p->chunks_list;
	p->chunks_list = chunk;
	return (chunk);
}

void				*pool_obtain_node(t_pool *p)
{
	void	*node;

	if (p->free_list == NULL)
	{
		if (pool_add_chunk(p) == NULL)
			return (NULL);
	}
	node = p->free_list;
	p->free_list = *(void**)p->free_list;
	return (node);
}

void				pool_release_node(t_pool *p, void *node)
{
	*(void**)node = p->free_list;
	p->free_list = node;
}
