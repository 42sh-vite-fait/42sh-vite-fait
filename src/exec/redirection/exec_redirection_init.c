#include "errors.h"
#include "exec.h"

int	startup_redirection_init(void)
{
	int	ret;
	
	if ((ret = exec_backup_standard_fd()) != NO_ERROR)
		return (ret);
	return (NO_ERROR);
}
