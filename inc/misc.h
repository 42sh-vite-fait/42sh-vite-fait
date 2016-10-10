#ifndef MISC_H
# define MISC_H

# include "typedefs_42.h"

// TODO rename buffer to string
t_buffer		*buffer_escape(t_buffer *b, int c);
t_buffer		*buffer_unescape(t_buffer *b, int c);

#endif
