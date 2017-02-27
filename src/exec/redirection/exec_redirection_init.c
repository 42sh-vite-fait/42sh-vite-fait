#include "errors.h"
#include "exec.h"

int	init_redirection_module(void)
{
	int	ret;
	
	if ((ret = exec_backup_standard_fd()) != NO_ERROR)
		return (ret);
	return (NO_ERROR);
}
