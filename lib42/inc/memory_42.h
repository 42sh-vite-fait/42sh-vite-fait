/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_42.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 16:28:49 by djean             #+#    #+#             */
/*   Updated: 2016/09/30 14:54:25 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_42_H
# define MEMORY_42_H

# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include "error_42.h"

# define MEM_WORD_LEN		sizeof(unsigned long int)
# define MEM_BLOCK_SIZE		(8 * MEM_WORD_LEN)
# define MEM_PAGE_SIZE		4096
# define HIGHBIT_0X01(n)	((n) - 0x0101010101010101UL)
# define HIGHBIT_0X80(n)	(~(n) & 0x8080808080808080UL)
# define HAS_ZERO(n)		(HIGHBIT_0X01(n) & HIGHBIT_0X80(n))
# define HAS_BYTE(n, cccc)	(HAS_ZERO(n ^ cccc))

void	*ft_memset(void *s, int c, size_t n);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memalloc(size_t size);
void	*malloc_or_die(size_t size);

#endif
