#include "opt.h"
#include "shell.h"

int		main(int argc, char *argv[])
{
	if (argc > 1)
		opt_parse(argc, argv);
	shell_loop();
}
