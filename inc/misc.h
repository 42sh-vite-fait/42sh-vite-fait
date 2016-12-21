#ifndef MISC_H
# define MISC_H

# include <stdlib.h>
# include <stdbool.h>
# include "typedefs_42.h"


bool			is_valid_alias_name(const char *string, size_t len);
bool			is_valid_name(const char *string, size_t len);
/*
** `is_escaped` take a 'pos'ition in an str and an 'end' pointer
** to stop reverse searching.
** Returns true if the pointed character (by 'pos') is escaped, false otherwise.
**
** `string_escape_chars` escapes all 'c' characters in the 's' string.
** Returns NULL if the function fails.
**
** `string_unescape_chars` unescapes all 'c' escaped characters
** in the 's' string. Returns NULL if the function fails.
**
*/
bool			is_escaped(const char *pos, const char *end);
t_string		*string_escape_chars(t_string *s, int c);
t_string		*string_unescape_chars(t_string *s, int c);

/*
** `string_read_from_fd` init and populatea the 's' string with the content
** of the 'fd' stream. Returns NULL if the function fails.
**
** `string_write_to_fd` write the 's' string inside the 'fd' stream.
** Returns 0 if the function succeed.
*/
t_string		*string_read_from_fd(t_string *s, int fd);
int				string_write_to_fd(const t_string *s, int fd);

#endif
