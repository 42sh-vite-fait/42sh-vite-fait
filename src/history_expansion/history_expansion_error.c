#include "history_expansion.h"
#include "ft_printf.h"

void		print_error(t_exp exp, t_string command)
{
	ft_dprintf(2, "Error in history_substitution: %.*s\n", exp.size, &command.str[exp.offset]);
}

void		free_data(t_exp *listexp, t_string *list,
				size_t expnum, size_t stringnum)
{
	size_t i;

	i = 0;
	while (i < expnum)
	{
		if (listexp[i].type == E_TYPE_STRING)
			string_shutdown(&listexp[i].string);
		i++;
	}
	i = 0;
	while (i < stringnum)
	{
		string_shutdown(&list[i]);
		i++;
	}
}
