#include "init.h"
#include "opt.h"
#include "shell.h"

int		main(int argc, char *argv[])
{
	extern char	**environ;
	int			ret;

	init_shell(argc, (const char *const*)argv, environ);
	ret = shell_loop();
	if (opt_is_set(OPT_INTERACTIVE))
		shell_history_shutdown();
	return (ret);
}
