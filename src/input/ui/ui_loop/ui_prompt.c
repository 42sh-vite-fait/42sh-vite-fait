#include "user_interface.h"

size_t	prompt(void)
{
	char *p;

	if ((p = getenv("PROMPT")) != NULL)
	{
		write(1, p, ft_strlen(p));
		return (ft_strlen(p));
	}
	else
	{
		write(1, "42sh> ", 6);
		return (6);
	}
}
