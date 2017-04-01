#ifndef TEST_LIB42_H
#define TEST_LIB42_H

#define _XOPEN_SOURCE 700
#define _DEFAULT_SOURCE
#define BIG_CHUNKS (1 << 16) // 65Ko

#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#if !defined(__APPLE__)
#include <bsd/string.h>
#endif
#include <stdint.h>
#include "lib42.h"
#include "vittf.h"

// Array
void	suite_array_create(void);
void	suite_array_init(void);
void	suite_array_at(void);
void	suite_array_reserve(void);
void	suite_array_shrink_to_fit(void);
void	suite_array_push(void);
void	suite_array_pop(void);
void	suite_array_index_of(void);
void	suite_array_replace_at(void);
void	suite_array_insert_at(void);
void	suite_array_remove_at(void);
void	suite_array_remove_elem(void);
void	suite_array_clone(void);
void	suite_array_truncate_clear(void);
void	suite_array_get_available(void);
void	suite_array_find_from(void);
void	suite_array_filter(void);
void	suite_array_swap(void);

// Cbuffer
void	suite_cbuffer_push(void);
void	suite_cbuffer_pop(void);
void	suite_cbuffer_reserve(void);
void	suite_cbuffer_truncate(void);
void	suite_cbuffer_shrink_to_fit(void);

// String
void	suite_string_macros(void);
void	suite_string_create_init(void);
void	suite_string_reserve(void);
void	suite_string_shrink_to_fit(void);
void	suite_string_dup(void);
void	suite_string_cat(void);
void	suite_string_insert(void);
void	suite_string_remove(void);
void	suite_string_set(void);
void	suite_string_truncate(void);
void	suite_string_remove_back(void);
void	suite_string_remove_back_chr(void);
void	suite_string_append(void);
void	suite_string_replace(void);
void	suite_string_clone(void);
void	suite_string_merge(void);

// Memory
void	suite_memcpy(void);
void	suite_memccpy(void);
void	suite_memcmp(void);
void	suite_memmove(void);
void	suite_memset(void);
void	suite_memchr(void);

// Stdlib
void	suite_realloc(void);
void	suite_toa_base(void);
void	suite_next_power_of_2(void);
void	suite_ato_base(void);

// Ctype
void	suite_ctype(void);

// Str
void	suite_strcmp(void);
void	suite_strlen(void);
void	suite_strnlen(void);
void	suite_strdup(void);
void	suite_strndup(void);
void	suite_strchr(void);
void	suite_strrchr(void);
void	suite_strrev(void);
void	suite_strstr(void);

// Pool
void	suite_pool_macros(void);
void	suite_pool_create(void);
void	suite_pool_init(void);
void	suite_pool_obtain_node(void);
void	suite_pool_release_node(void);
void	suite_pool_shutdown(void);

// Error
void	suite_error(void);

// unistd

void	suite_getopt(void);

#endif
