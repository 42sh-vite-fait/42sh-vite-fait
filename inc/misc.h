#ifndef MISC_H
# define MISC_H

# include <stdbool.h>
# include "typedefs_42.h"

bool			is_escaped(const char *pos, const char *end);
t_string		*string_escape_chars(t_string *b, int c);
t_string		*string_unescape_chars(t_string *b, int c);

t_string		*string_read_from_fd(t_string *b, int fd);
int				string_write_to_fd(const t_string *b, int fd);

#endif
