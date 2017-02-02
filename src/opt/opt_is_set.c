#include <stdbool.h>
#include "opt.h"

extern unsigned	g_opt_debug;

bool opt_is_set(unsigned opt)
{
	return (g_opt_debug & opt);
}
