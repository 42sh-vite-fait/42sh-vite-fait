
#ifndef BUILTINS_H
# define BUILTINS_H

# include <stddef.h>
# include <stdbool.h>

/*
** Builtin interface
*/
typedef int		t_builtin(int ac, char *const *av,
					char *const *env);

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
int				exec_builtin(int ac, char *const *av, char *const *env);

/*
** Tells if `name` corresponds to a builtin.
*/
bool			is_builtin(const char *name, size_t len);

#endif
