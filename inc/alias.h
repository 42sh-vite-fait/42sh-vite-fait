#ifndef ALIAS_H
# define ALIAS_H

# include "typedefs_42.h"
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
** `alias_clear` remove all aliases
*/
void			alias_clear(void);

/*
** `alias_get_all` return the internal t_array of all aliases
*/
const t_array	*alias_get_all(void);

/*
** `alias_get_value` returns the value of the existing alias.
**
** `alias_set` create the alias with the given 'name' and 'value',
** and set (erase and create) the alias if it already exists.
** 'name_value' is not duplicated.
**
** `alias_unset` delete the alias corresponding to the given 'name'.
** Returns -1 if the alias is not found.
*/
const char		*alias_get_value(const char *name);
int				alias_set(char *name_value);
int				alias_unset(const char *name);

#endif
