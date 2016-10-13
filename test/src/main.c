#include "header.h"

int	main(void)
{
	// Buffer
	suite_buffer_escape();

	// history
	suite_history();

	v_full_success("42sh");
	return (0);
}
