#ifndef ALIAS_H
# define ALIAS_H

# include "typedefs_42.h"
# include "string_42.h"
# include "array_42.h"

struct		s_alias
{
	t_array		aliases;
};

typedef struct s_alias	t_alias;

/*
** `alias_init` initialize the alias module, returns 0 if no error occurs.
**
** `alias_shutdown` free each alias and shutdown the internal array.
*/
int				alias_init(void);
void			alias_shutdown(void);

/*
** `alias_get` returns the value of the existing alias.
**
** `alias_set` create the alias with the given 'name' and 'value,
** and set (erase and create) the alias if it already exists.
** 'name' and 'value' are duplicated.
*/
const t_string	*alias_get(const char *name);
int				alias_set(const char *name, const t_string *value);

#endif
