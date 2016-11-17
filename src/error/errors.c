#include "errors.h"
#include "error_42.h"

static char	*g_errors_list[] = {
	[NO_ERROR] = "no error",
	[ERR_MALLOC] = "malloc failed !",
};

void	errors_init(void)
{
	register_errlist("42sh", g_errors_list, ARR_SIZ_MAX(g_errors_list));
}

