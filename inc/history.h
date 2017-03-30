/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 17:00:15 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 17:13:50 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include <stdlib.h>
# include <stdbool.h>
# include "typedefs_42.h"
# include "structs_42.h"
# include "cbuffer_42.h"

/*
** HISTSIZE custom maximal value
*/
# define HIST_MAX_SIZE 10000

/*
** HISTSIZE minimal value mandated by POSIX
*/
# define HIST_DEFAULT_SIZE 128

/*
** HISTFILE default value mantated by POSIX
*/
# define HIST_DEFAULT_FILE "/.sh_history"

struct			s_history
{
	t_cbuffer	commands;
	size_t		last_id;
};

struct			s_result
{
	size_t	command_id;
	size_t	offset;
};

typedef struct s_history	t_history;
typedef struct s_result		t_result;

/*
** `history_init` initialize the history with a limited capacity,
** returns zero if no error occurs.
**
** `history_shutdown` desallocate internal commands.
** Using the history after a call of this function gives unspecified behaviours.
*/
int				history_init(size_t limit);
void			history_shutdown(void);

/*
** `history_clear` clear all commands saved in the history, last_id become 0.
*/
void			history_clear(void);

/*
** `history_save_into_file` create the file at 'path' (O_RDWR | O_TRUNC, 0600),
** write each command and escape the '\n', returns zero if no error occurs.
**
** `history_load_from_file` will read the file at 'path' (O_RDONLY) and
** add each command paying attention to escaped '\n' inside commands,
** returns zero if no error occurs.
*/
int				history_save_into_file(const char *path);
int				history_load_from_file(const char *path);

/*
** `history_add` push a 'command' to the history and returns its id. Returns 0
** in error case.
** The given t_string* is not copied, on history destruction
** each command is fread.
*/
size_t			history_add(t_string *command);

/*
** `history_get` returns the command with the specified 'id',
** returns NULL if the 'id' don't exist in the history.
**
** `history_get_last_id` returns the last added command id.
** Returns 0 if history is empty, 0 is an invalid id, IDs starts at 1.
**
** `history_get_first_id` returns the oldest command id.
** Returns an id > 0, or 0 if history is empty.
**
** `history_get_last_str_id` returns the id of the newest entry
** beginning with `str`.
** Returns an id > 0 if such entry is found, 0 otherwise.
*/
const t_string	*history_get(size_t id);
size_t			history_get_last_id(void);
size_t			history_get_first_id(void);
size_t			history_get_last_str_id(const char *str);

/*
** `history_find` find the last matching pattern starting from
** the last character of the last added command, returns true
** if it matchs something, filling the 't_result *ret' struct
** (if not NULL) with offset and id of the matching command.
** Returns false if no command match, don't fill the 't_result *ret'
**
** `history_find_from` find the next matching command (previous), returns true
** if it find something and fill 't_result *ret' (if not NULL). Retruns false if
** no command match.
**
** `history_find_start_with` find the first command (previous) that starts with
** the given pattern, returns true if it find something and fill 't_result *ret'
** (if not NULL). Returns false if no command match.
*/
bool			history_find(t_result *ret, const char *pattern);
bool			history_find_from(t_result *ret, const char *p, t_result from);
bool			history_find_start_with(t_result *res, const char *pattern);

#endif
