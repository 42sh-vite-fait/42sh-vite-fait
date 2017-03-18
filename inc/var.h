#ifndef VAR_H
# define VAR_H

void			var_init(char **environ);
void			var_shutdown(void);
void			var_clear(void);
int				var_set(const char *name, const char *value);
int				var_unset(const char *name);
int				var_get(const char *name, const char **value);
char * const	*var_get_environ(void);

#endif
