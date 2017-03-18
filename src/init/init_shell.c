#include "shell.h"
#include "terminal.h"
#include "opt.h"
#include "errors.h"
#include "exec.h"
#include "var.h"
#include "sig.h"
#include "history.h"

static void	update_shell_lvl(void)
{
	const char    *value;

	var_get("SHLVL", &value);
	if (value == NULL)
		var_set("SHLVL", "1", VAR_ATTR_EXPORT);
	else
	{
		value = ft_utoa_base(ft_atou_base(value, 10) + 1, 10);
		fatal_malloc((void*)value);
		var_set("SHLVL", value, VAR_ATTR_EXPORT);
		free((void*)value);
	}
}

void		init_shell(int argc, const char *const *argv, char **environ)
{
	opt_parse(argc, argv);
	if (init_exec_fd() != OK_) // TODO: que faire si ./42 <&-
	{
		error_print("init");
		exit(1);
	}
	var_init_with_environ(environ);
	update_shell_lvl();
	if (opt_is_set(OPT_INTERACTIVE))
	{
		if (init_terminal_module() != OK_)
		{
			error_print("terminal");
			exit(1);
		}
		init_signal_module();
		shell_history_init();
	}
}
