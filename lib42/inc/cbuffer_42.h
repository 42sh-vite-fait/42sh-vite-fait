/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbuffer_42.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 16:28:48 by djean             #+#    #+#             */
/*   Updated: 2016/10/21 11:26:27 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CBUFFER_42_H
# define CBUFFER_42_H

# include <stdlib.h>
# include "typedefs_42.h"

# define CBUFFER_AT_INDEX(b, i) ((char*)(b)->data + ((b)->elem_size * (i)))
# define CBUFFER_MOVE_BACKWARD(l, n) ((n) ? (n) - 1 : (l) - 1)
# define CBUFFER_MOVE_FORWARD(l, n) ((n) >= l - 1 ? 0 : (n) + 1)

/*
** `cbuffer_create` alloc a new t_cbuffer, use 'delete_func' to destroy
** internal elements. Give NULL to 'delete_func' if not needed.
**
** `cbuffer_destroy` desallocate the given `t_buffer *`, call 'delete_func'
** on each element and free the internal malloc.
*/
t_cbuffer	*cbuffer_create(size_t capacity, size_t elem_size,
							void (*delete_func)(void *));
void		cbuffer_destroy(t_cbuffer *buffer);

/*
** `cbuffer_init` init a given buffer, use 'delete_func' to destroy
** internal elements. Give NULL to 'delete_func' if not needed.
**
** `cbuffer_shutdown` call 'delete_func' on each element and
** free the internal malloc.
*/
t_cbuffer	*cbuffer_init(t_cbuffer *buffer, size_t capacity, size_t elem_size,
							void (*delete_func)(void *));
void		cbuffer_shutdown(t_cbuffer *buffer);

/*
** `cbuffer_reserve` enlarge the capacity of the buffer if (len + 'additional')
** is bigger than actual capacity.
**
** `cbuffer_shrink_to_fit`reduce the capacity of the 'internal data' to
** be the closest to the buffer len.
*/
t_cbuffer	*cbuffer_reserve(t_cbuffer *buffer, size_t additional);
t_cbuffer	*cbuffer_shrink_to_fit(t_cbuffer *buffer);

/*
** `cbuffer_truncate_from_back` pop enought element from the back
** to get a len of 'n'. If truncate is larger than actual len it return NULL
** and do nothing.
**
** `cbuffer_truncate_from_front` pop enought element from the front
** to get a len of 'n'. If truncate is larger than actual len it return NULL
** and do nothing.
*/
t_cbuffer	*cbuffer_truncate_from_back(t_cbuffer *buffer, size_t n);
t_cbuffer	*cbuffer_truncate_from_front(t_cbuffer *buffer, size_t n);

/*
** `cbuffer_push_back` push the 'elem' to the back of the buffer.
** Call delete_func if the pushed element overwrite another in the buffer.
**
** `cbuffer_push_front` push the 'elem' to the front of the buffer.
** Call delete_func if the pushed element overwrite another in the buffer.
*/
void		cbuffer_push_back(t_cbuffer *buffer, const void *elem);
void		cbuffer_push_front(t_cbuffer *buffer, const void *elem);

/*
** `cbuffer_pop_back` returns the popped element from the back
** or NULL if the len is zero.
**
** `cbuffer_pop_front` returns the popped element from the front
** or NULL if the len is zero.
*/
void		*cbuffer_pop_back(t_cbuffer *buffer);
void		*cbuffer_pop_front(t_cbuffer *buffer);

/*
** `cbuffer_get_at` returns the element at the given index
** or NULL if out of range.
**
** `cbuffer_get_front` returns the element on front or NULL if the len is zero.
**
** `cbuffer_get_back` returns the element on back or NULL if the len is zero.
*/
void		*cbuffer_get_at(const t_cbuffer *buffer, size_t i);
void		*cbuffer_get_front(const t_cbuffer *buffer);
void		*cbuffer_get_back(const t_cbuffer *buffer);

#endif
