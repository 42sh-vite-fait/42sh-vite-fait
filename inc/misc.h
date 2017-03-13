#ifndef MISC_H
# define MISC_H

# include <stdlib.h>
# include <stdbool.h>
# include "typedefs_42.h"


bool			is_valid_alias_name(const char *string, size_t len);
bool			is_valid_name(const char *string, size_t len);
bool			is_valid_variable(const char *str);

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

/*
** 'ft_tmpfile' return a filename for a temporary file.
** The 'prefix' arg, if not NULL, will be prepend to the filename
*/

char	*ft_tmpfile(const char *prefix);

/*
** `get_next_path` is meant to iterate through the PATH
** environment variable.
** `paths` is a pointer to a colon-separated list of folders.
** It is incremented with each call.
** `path` is filled with a path. The t_string shall be initialized.
** The function returns `paths` incremented for the next
** path, or NULL if `paths` contains no more paths.
*/
const char	*get_next_path(t_string *path, char const *paths);

/*
** `str_token` is used to isolate tokens delimited by `sep`
** in the null-terminated string `input`. `token` contains
** said token.
** `str_token` returns `input` stepped forward for the next token,
** or NULL if no token remains.
*/
const char	*str_token(t_string *token, const char *input, char sep);

#endif
