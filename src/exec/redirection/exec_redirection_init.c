#include "errors.h"
#include "exec.h"

int	init_redirection_module(void)
{
	int	ret;
	
	if ((ret = exec_backup_standard_fd()) != OK_)
		return (ret);
	return (OK_);
}
