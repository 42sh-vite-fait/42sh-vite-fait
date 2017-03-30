/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio_42.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:41:36 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 16:41:37 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STDIO_42_H
# define STDIO_42_H

# include <unistd.h>
# include "ctype_42.h"

/*
** ft_print_memory
*/
# define BYTE_PER_BLOCK	2
# define ASCII_PER_LINE	16
# define NB_PRINT_HEX	2 * ASCII_PER_LINE
# define NB_PRINT_SPACE	ASCII_PER_LINE / BYTE_PER_BLOCK
# define NB_COLUMNS		NB_PRINT_HEX + NB_PRINT_SPACE

void	ft_print_memory(const void *addr, size_t size);

#endif
