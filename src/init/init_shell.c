#include "shell.h"
#include "terminal.h"
#include "opt.h"
#include "errors.h"
#include "exec.h"
#include "var.h"
#include "sig.h"
#include "history.h"
#include "builtins.h"

extern t_string	g_pwd;

static int	set_cwd(void)
{
	const char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		error_set_context("getcwd: %s", strerror(errno));
		return (ERROR_);
	}
	var_set("PWD", pwd);
	fatal_malloc(string_init_dup(&g_pwd, pwd));
	free((void*)pwd);
	return (OK_);
}

static void	update_shell_lvl(void)
{
	const char    *value;

	if (var_get("SHLVL", &value) == ERROR_)
		var_set("SHLVL", "1");
	else
	{
		value = ft_utoa_base(ft_atou_base(value, 10) + 1, 10);
		fatal_malloc((void*)value);
		var_set("SHLVL", value);
		free((void*)value);
	}
}

void		init_shell(int argc, const char *const *argv, char **environ)
{
	opt_parse(argc, argv);
	if (init_exec_module() != OK_)
	{
		error_print("init");
		exit(1);
	}
	var_init(environ);
	update_shell_lvl();
	if (set_cwd() != OK_)
	{
		error_print("init");
		exit(1);
	}
	if (opt_is_set(OPT_INTERACTIVE))
	{
		if (init_terminal_module() != OK_)
		{
			error_print("terminal");
			exit(1);
		}
		init_signal_module();
	}
	shell_history_init();
}
