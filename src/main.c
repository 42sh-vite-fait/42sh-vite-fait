#include "opt.h"
#include "shell.h"
#include "terminal.h"
#include "history.h"
#include "sig.h"
#include "var.h"
#include "exec.h"

int		main(int argc, char *argv[])
{
	opt_parse(argc, (const char * const *)argv);
	init_signal_module();
	exec_backup_standard_fd(); // TODO: que faire si ./42sh <&-
	if (opt_is_set(OPT_INTERACTIVE) && init_terminal_module() != NO_ERROR)
	{
		error_print("terminal");
		exit(1);
	}
	var_init();
	history_init(4);
	return (shell_loop());
}
