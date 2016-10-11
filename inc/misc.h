#ifndef MISC_H
# define MISC_H

# include <stdbool.h>
# include "typedefs_42.h"

# define BUFFER_READ (4096) // TODO pagesize

// TODO rename buffer to string
bool			is_escaped(const char *pos, const char *end);
t_buffer		*buffer_escape_chars(t_buffer *b, int c);
t_buffer		*buffer_unescape_chars(t_buffer *b, int c);

t_buffer		*buffer_read_from_fd(int fd);
int				buffer_write_to_fd(t_buffer *b, int fd);

#endif
