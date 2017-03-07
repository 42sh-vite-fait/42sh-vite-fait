#include "exit_status.h"

static int g_exit_status_last = 0;

int exit_status_get_last(void)
{
	return (g_exit_status_last);
}

void exit_status_set_last(int exit_status)
{
	g_exit_status_last = exit_status;
}
