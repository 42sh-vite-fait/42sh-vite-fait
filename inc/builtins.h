#ifndef BUILTINS_H
# define BUILTINS_H

# include "ast.h"

int		exec_builtin(const t_command command);
bool 	is_builtin(const char *cmd, size_t len);
int		builtin_history(int ac, char *const *av);

#endif
