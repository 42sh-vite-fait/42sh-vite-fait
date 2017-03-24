#include <assert.h>
#include "autocompletion.h"
#include "var.h"
#include "errors.h"

void	autocomplete(t_array *matches, const char *cmd, size_t len)
{
	const char	*pwd;
	const char	*path;
	char		*cmd_cpy;

	cmd_cpy = fatal_malloc(ft_strndup(cmd, len));
	if (ft_strchrpos(cmd_cpy, '/') != -1)
		complete_path(matches, cmd_cpy);
	else
	{
		complete_builtin(matches, cmd_cpy);
		if (var_get("PWD", &pwd) == OK_)
			complete_cmd_in_pwd(matches, cmd_cpy, pwd);
		if (var_get("PATH", &path) == OK_)
			complete_cmd_in_paths(matches, cmd_cpy, path);
	}
	free(cmd_cpy);
}
