#ifndef MISC_H
# define MISC_H

# include <stdbool.h>
# include "typedefs_42.h"

bool			is_escaped(const char *pos, const char *end);
t_buffer		*buffer_escape_chars(t_buffer *b, int c);
t_buffer		*buffer_unescape_chars(t_buffer *b, int c);

t_buffer		*buffer_read_from_fd(t_buffer *b, int fd);
int				buffer_write_to_fd(const t_buffer *b, int fd);

#endif
