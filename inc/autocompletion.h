#ifndef AUTOCOMPLETION_H
# define AUTOCOMPLETION_H

#include "array_42.h"

void	autocomplete(t_array *matches, const char *cmd, size_t len);

void	complete_path(t_array *matches, const char *path);
void	complete_cmd_in_paths(t_array *matches, const char *name,
							const char *paths);
void	complete_cmd_in_pwd(t_array *matches, const char *cmd,
							const char *pwd);

void	complete_builtin(t_array *matches, const char *name);

#endif
