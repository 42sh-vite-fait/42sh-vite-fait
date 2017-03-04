#include <stdbool.h>
#include "opt.h"

extern unsigned	g_opt_shell;

bool opt_is_set(unsigned opt)
{
	return (g_opt_shell & opt);
}
