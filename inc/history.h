#ifndef HISTORY_H
# define HISTORY_H

# include <stdlib.h>
# include <stdbool.h>
# include "typedefs_42.h"
# include "structs_42.h"
# include "cbuffer_42.h"

struct		s_history
{
	t_cbuffer	commands;
	size_t		last_id;
};

struct		s_result
{
	size_t	command_id;
	size_t	offset;
};

typedef struct s_history	t_history;
typedef struct s_result		t_result;

/*
** history_init initialize g_history with a limited len,
** returning zero if no error occurs.
*/
int				history_init(size_t limit);

/*
** history_save_into_file create the file at path (O_RDWR | O_TRUNC, 0600)
** and write each command and escape the '\n' inside commands,
** returning zero if no error occurs.
**
** history_load_from_file will read the file at path (O_RDONLY) and
** add each command paying attention to escaped '\n' inside commands,
** returning zero if no error occurs.
*/
int				history_save_into_file(const char *path);
int				history_load_from_file(const char *path);

/*
** history_add push a command to the history and return the id to retrieve it.
*/
size_t			history_add(t_buffer command);

/*
** history_get return the command with the specified id,
** returning NULL if the id doesn't exist in the history;
**
** history_get_last_id returns the last added command id.
*/
const t_buffer	*history_get(size_t id);
size_t			history_get_last_id(void);

/*
** history_find find the last matching pattern starting form the last character
** of the last added command, returning true if it matchs something,
** filling correctly the t_result *ret struct (if not NULL) with offset and id
** of the matching command.
**
** history_find_from find the next matching command (previous), returning true
** if it found something and filling correctly t_result *ret (if not NULL).
**
** history_find_start_with find the first command (previous) starting with
** the given pattern, returning true if it found something and filling
** correctly t_result *ret (if not NULL).
*/
bool			history_find(t_result *ret, const char *pattern);
bool			history_find_from(t_result *ret, const char *p, t_result from);
bool			history_find_start_with(t_result *res, const char *pattern);

#endif
