/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_42.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 16:28:48 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 16:42:32 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_42_H
# define STRING_42_H

# include <stdlib.h>
# include "typedefs_42.h"
# include "structs_42.h"
# include "memory_42.h"
# include "stdlib_42.h"
# include "str_42.h"

# define STRING_INIT_SIZE		(64U)

/*
** `string_create` and `string_create_with_capacity` malloc a new `t_string`
** and a new 'internal str' with default size or (capacity + 1) if specified.
**
** `string_destroy` free the `t_string*` and the 'internal str'.
*/
t_string	*string_create(void);
t_string	*string_create_with_capacity(size_t capacity);
void		string_destroy(t_string *s);

/*
** `string_init` and `string_init_with_capacity` initialize an already
** existing string 's': malloc the 'internal str' with default size
** or (capacity + 1) if specified.
**
** `string_shutdown` free the 'internal str'.
*/
t_string	*string_init(t_string *s);
t_string	*string_init_with_capacity(t_string *s, size_t capacity);
void		string_shutdown(t_string *s);

/*
** `string_init_dup` and `string_init_ndup` init the `t_string` param
** with the given 'str', duplicating it.
** The new string capacity is the next power of 2 of the str length
** if not already a power of 2.
**
** `string_create_dup` and `string_create_ndup` malloc a new `t_string`
** and call `string_init_dup` or `string_init_ndup`.
** The new string capacity is the next power of 2 of the str length
** if not already a power of 2.
*/
t_string	*string_init_dup(t_string *s, const char *str);
t_string	*string_init_ndup(t_string *s, const char *str, size_t len);
t_string	*string_create_dup(const char *str);
t_string	*string_create_ndup(const char *str, size_t len);

/*
** `t_string_clone` do the same as `string_dup` but with another `t_string`.
**
** `string_merge` concatenate the two strings 'a' and 'b',
** in the string 's'. 's' will be init inside this function.
*/
t_string	*string_clone(t_string *dst, const t_string *src);
t_string	*string_merge(t_string *dst, const t_string *a, const t_string *b);

/*
** `string_cat` and `string_ncat` concatenate another 'str'
** to the actual string.
**
** `string_append` do the same as `string_cat` but with another `t_string`.
*/
t_string	*string_cat(t_string *s, const char *str);
t_string	*string_ncat(t_string *s, const char *str, size_t len);
t_string	*string_append(t_string *dst, const t_string *src);

/*
** `string_replace` and `string_nreplace` rewrite on the entire buffer,
** reserving enought space to write the new str entirely.
**
** `string_set` replace from the given position 'from',
** 'n' characters by the specified 'c' char. Return NULL if 'from' is bigger
** than the string's len.
*/
t_string	*string_replace(t_string *s, const char *str);
t_string	*string_nreplace(t_string *s, const char *str, size_t len);
t_string	*string_set(t_string *s, size_t from, size_t n, int c);

/*
** `string_insert` insert at the 'pos' the string 'str' of size 'l'.
*/
t_string	*string_insert(t_string *s, size_t pos, const char *str, size_t l);

/*
** `string_remove` removes at position 'pos' a number 'n' of chars.
** It returns the numbers of chars effectively removed.
**
** `string_remove_back` remove back 'n' chars. It returns the new len
** of the string, -1 if the truncate is to large.
**
** `string_remove_back_chr` remove back all chars after the last char 'c' found.
** It returns the number of chars truncated, -1 if 'c' was not found.
*/
size_t		string_remove(t_string *s, size_t pos, size_t n);
ssize_t		string_remove_back(t_string *s, size_t n);
ssize_t		string_remove_back_chr(t_string *s, int c);

/*
** `string_reserve` enlarge the capacity of the string if (len + 1 + additional)
** is bigger than actual capacity.
**
** `string_shrink_to_fit` reduce the capacity of the 'internal str' to
** be the closest to the string length.
**
** `string_truncate` truncates the string.
** It returns NULL if the truncate is to large.
*/
t_string	*string_reserve(t_string *s, size_t additional);
t_string	*string_shrink_to_fit(t_string *s);
t_string	*string_truncate(t_string *s, size_t n);

#endif
