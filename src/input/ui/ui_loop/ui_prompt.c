#include "user_interface.h"

size_t prompt(const char *prompt)
{
	ft_printf("%s", prompt);
	return (ft_strlen(prompt));
}
