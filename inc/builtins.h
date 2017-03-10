#ifndef BUILTINS_H
# define BUILTINS_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdint.h>
# include "lib42.h"
# include "string_42.h"

/*
** Builtin interface
*/
typedef int		t_builtin(int ac, const char *const *av);

typedef struct	s_pair_name_builtin
{
	char		*name;
	t_builtin	*builtin;
}				t_pair_name_builtin;

/*
** Executes a builtin with generic arguments.
** The builtin name shall be the first field of `av`.
** Returns the same value as the executed builtin, or -1
** if none is found.
*/
int				exec_builtin(int ac, const char *const *av);

/*
** Tells if `name` corresponds to a builtin.
*/
bool			is_builtin(const char *name, size_t len);

/*
** Builtins
*/

int builtin_exit(int ac, const char * const *av);
//int builtin_history(int argc, const char *const *argv); change sig
int builtin_echo(int argc, const char *const *argv);
int echo_handlers_alert(const char *arg, t_string *buf);
int echo_handlers_backspace(const char *arg, t_string *buf);
int echo_handlers_no_newline(const char *arg, t_string *buf);
int echo_handlers_form_feed(const char *arg, t_string *buf);
int echo_handlers_newline(const char *arg, t_string *buf);
int echo_handlers_carriage_return(const char *arg, t_string *buf);
int echo_handlers_tab(const char *arg, t_string *buf);
int echo_handlers_vertical_tab(const char *arg, t_string *buf);
int echo_handlers_backslash(const char *arg, t_string *buf);
int echo_handlers_num(const char *arg, t_string *buf);


#endif
