#include "input.h"
#include "ft_printf.h"

int		main(void)
{
	char	*input;

	while (42)
	{
		ft_printf("$> ");
		input = input_readline();
		ft_printf("===> %s\n", input);
		if (ft_strcmp(input, "exit") == 0)
			exit(0);
	}
}
