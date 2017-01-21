#ifndef ERRORS_H
# define ERRORS_H

# include <errno.h>

# define BIN_NAME "42sh"
# define NO_ERROR (0)

extern int	errno;

void	error_set_context(const char *format, ...);
void	error_print(const char *module_name);

#endif
