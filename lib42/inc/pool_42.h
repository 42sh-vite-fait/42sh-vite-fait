/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool_42.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 18:43:08 by djean             #+#    #+#             */
/*   Updated: 2016/11/22 16:27:12 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POOL_42_H
# define POOL_42_H

# include <stdlib.h>
# include "typedefs_42.h"
# include "structs_42.h"

# define MAX_CHUNK_SIZE		(4096)
# define CHUNK_CAPACITY(e)	((MAX_CHUNK_SIZE - sizeof(void*)) / (e))
# define ROUND_UP_8(n)		(!(n) || (n) % 8U ? ((n) + 8U) & (~0U - 7U) : (n))
# define CHUNK_HEAD(c)		(&(c)->head)

/*
** `pool_create` malloc a new `t_pool` and initialize the intern fields
**
** `pool_destroy` free the `t_pool` and the internal chunks
*/
t_pool		*pool_create(size_t elem_size);
void		pool_destroy(t_pool *p);

/*
** `pool_init` initialize the intern fields
**
** `pool_shutdown` free all chunks in the pool
*/
t_pool		*pool_init(t_pool *p, size_t elem_size);
void		 pool_shutdown(t_pool *p);

/*
** `pool_obtain_node` return the head of the freelist and update the freelist
** for the next free node
** Get a new chunk if the freelist is empty
**
** `pool_release_node` add `node` as the new head of the freelist
** No verification is made to know if `node` belongs to the pool
*/
t_chunk		*pool_add_chunk(t_pool *p);
void		*pool_obtain_node(t_pool *p);
void		pool_release_node(t_pool *p, void *node);

#endif
