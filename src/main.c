#include "opt.h"
#include "shell.h"
#include "terminal.h"
#include "history.h"

int		main(int argc, char *argv[])
{
	opt_parse(argc, argv);
	if (init_terminal_module() != NO_ERROR)
	{
		error_print("terminal");
		exit(1);
	}
	history_init(4);
	return (shell_loop());
}
