#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdbool.h>
# include <stdlib.h>
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

int				builtin_exit(int ac, const char * const *av);
int				builtin_history(int argc, const char *const *argv);
int				builtin_echo(int argc, const char *const *argv);
int				builtin_env(int argc, const char *const *argv);
int				builtin_setenv(int argc, const char * const *argv);
int				builtin_unsetenv(int argc, const char * const *argv);

int				builtin_cd(int argc, const char * const *argv);
int				builtin_cd_rule_8(t_string *curpath);
const char		*get_next_component(t_string *component, const char *path);
void			get_base_path(t_string *curpath, bool *must_print_pwd,
								const char *dir);
int				physical_resolution(t_string *curpath);
int				logical_resolution(t_string *curpath, t_string backup,
									const char *pwd);

#endif
