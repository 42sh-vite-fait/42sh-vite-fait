#include "opt.h"
#include "shell.h"
#include "terminal.h"

int		main(int argc, char *argv[])
{
	opt_parse(argc, argv);
	if (init_terminal_module() != NO_ERROR)
	{
		error_print("terminal");
		exit(1);
	}
	return (shell_loop());
}
