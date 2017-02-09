#include "opt.h"
#include "shell.h"

int		main(int argc, char *argv[])
{
	opt_parse(argc, argv);
	return (shell_loop());
}
