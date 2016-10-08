#include "header.h"

static void		test_00_history_push(void)
{
	t_history	history;

	history_init(&history, 10000);
	VTS;
}

void			suite_history(void)
{
	test_00_history_push();

	VSS;
}
