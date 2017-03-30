/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_42.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 16:28:48 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 16:40:20 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_42_H
# define ARRAY_42_H

# include <stdlib.h>
# include <stdint.h>
# include "typedefs_42.h"
# include "structs_42.h"
# include "memory_42.h"
# include "stdlib_42.h"
# include "str_42.h"

# define ARRAY_INIT_SIZE	(8U)
# define ARRAY_IS_EMPTY(a)	((a)->len == 0)

/*
** `array_create` and `array_create_with_capacity` malloc a new `t_array`
** and a new 'internal buffer' with
** (default size) * elem_size or capacity * elem_size if specified.
**
** `array_destroy` free the `t_array*` and the 'internal buffer'.
*/
t_array		*array_create(size_t elem_size);
t_array		*array_create_with_capacity(size_t elem_size, size_t capacity);
void		array_destroy(t_array *a);

/*
** `array_init` and `array_init_with_capacity` initialize an already
** existing array 'a': malloc the 'internal buffer' with
** (default size) * elem_size or capacity * elem_size if specified.
**
** `array_shutdown` free the 'internal buffer'.
*/
t_array		*array_init(t_array *a, size_t elem_size);
t_array		*array_init_with_capacity(t_array *a, size_t elem_size,
		size_t capacity);
void		array_shutdown(t_array *a);

/*
** `array_reserve` enlarge the capacity of the array if (len + additional)
** is bigger than actual capacity.
**
** `array_shrink_to_fit` reduce the capacity of the 'internal buffer' to
** be the closest to the array length.
**
** `array_truncate` truncates the array.
** It returns NULL if the truncate is to large.
**
** `array_clear` set the len of the array to 0.
*/
t_array		*array_reserve(t_array *a, size_t additional);
t_array		*array_shrink_to_fit(t_array *a);
t_array		*array_truncate(t_array *a, size_t n);
void		array_clear(t_array *a);

/*
** `array_clone` initialize a new `t_array` with the internal data of 'src'.
*/
t_array		*array_clone(t_array *dst, const t_array *src);

/*
** `array_get_at` returns the pointer on the data at the specified index,
** NULL if the index is out of range.
**
** `array_set_at` copy the element 'e' in the array at the index specified,
** returns the pointer on the element in the array,
** NULL if the index is out of range.
**
** `array_index_of` returns the index of a given pointer, -1 if the pointer
** is not inside the array.
**
** `array_get_last` returns the pointer on the data of the last index, or NULL
** if the array is empty
**
** `array_get_first` returns the pointer on the data of the first index, or NULL
** if the array is empty
*/
void		*array_get_at(const t_array *a, size_t i);
void		*array_set_at(t_array *a, size_t i, const void *e);
ssize_t		array_index_of(const t_array *a, const void *e);
void		*array_get_last(const t_array *a);
void		*array_get_first(const t_array *a);

/*
** `array_insert_at` insert an element at the specified index,
** returns NULL if the index is out of bounds.
**
** `array_replace_at` replace the element at the given index and
** if old is not NULL, write the element inside it. Returns NULL if the index
** is out of bounds.
**
** `array_get_available` gives a new unitialized space at the end of the array,
** returns its pointer or NULL if an error occurs.
*/
t_array		*array_insert_at(t_array *a, size_t i, const void *e);
t_array		*array_replace_at(t_array *a, size_t i, const void *e, void *old);
void		*array_get_available(t_array *a);

/*
** `array_remove_at` removes the element at the given index, if 'removed'
** is not NULL, the old data is written inside it. Returns NULL if the index
** is out of bounds.
**
** `array_remove_elem` removes the element with the address equal to 'e'.
** Returns NULL if element isn't in the array.
*/
t_array		*array_remove_at(t_array *a, size_t i, void *removed);
t_array		*array_remove_elem(t_array *a, const void *e);

/*
** `array_push` insert an element at the end of the array.
**
** `array_pop` remove the last element of the array. if 'old'
** is not NULL, the old data is written inside it.
*/
t_array		*array_push(t_array *a, const void *e);
t_array		*array_pop(t_array *a, void *old);

void		*array_find_from(t_array set, size_t n,
		int (match)(const void *elem, const void *param), const void *param);
void		*array_find(t_array set,
		int (match)(const void *elem, const void *param), const void *param);

/*
** `array_swap` switch the elements at the index `e1` and `e2`
*/
t_array		*array_swap(t_array *a, size_t e1, size_t e2);

#endif
