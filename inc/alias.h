#ifndef ALIAS_H
# define ALIAS_H

# include "typedefs_42.h"
# include "string_42.h"
# include "array_42.h"

typedef t_array	t_alias;

/*
** `alias_init` initialize the alias module, returns 0 if no error occurs.
**
** `alias_shutdown` free each alias and shutdown the internal array.
*/
int				alias_init(void);
void			alias_shutdown(void);

/*
** `alias_get_value` returns the value of the existing alias.
**
** `alias_set` create the alias with the given 'name' and 'value,
** and set (erase and create) the alias if it already exists.
** 'name' is no kept and 'value' is not duplicated.
**
** `alias_unset` delete the alias corresponding to the given name.
** Returns -1 if the alias is not found.
*/
const char		*alias_get_value(const t_string *name);
int				alias_set(t_string *name_value);
int				alias_unset(const t_string *name);

#endif
