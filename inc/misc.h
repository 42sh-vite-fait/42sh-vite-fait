#ifndef MISC_H
# define MISC_H

# include "typedefs_42.h"

# define BUFFER_READ (4096) // TODO pagesize

// TODO rename buffer to string
t_buffer		*buffer_escape(t_buffer *b, int c);
t_buffer		*buffer_unescape(t_buffer *b, int c);

t_buffer		*buffer_read_from_fd(int fd);
int				buffer_write_to_fd(t_buffer *b, int fd);

size_t			rev_count_dup(const char *from, const char *to, int c);

#endif
