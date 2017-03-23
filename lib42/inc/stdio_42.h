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
