#include "opt.h"
#include "shell.h"
#include "terminal.h"
#include "history.h"
#include "sig.h"
#include "var.h"
#include "exec.h"

int		main(int argc, char *argv[])
{
	extern char	**environ;
	int			ret;

	// TODO ajouter un module d'init pour le shell
	opt_parse(argc, (const char * const *)argv);
	exec_backup_standard_fd(); // TODO: que faire si ./42sh <&-
	var_init_with_environ(environ);
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
	ret = shell_loop();
	if (opt_is_set(OPT_INTERACTIVE))
		shell_history_shutdown();
	return (ret);
}
