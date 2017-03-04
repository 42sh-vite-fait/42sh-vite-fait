#include "history_expansion.h"

void		print_error(t_exp exp, t_string command)
{
	(void)write(2, "Error in history_substitution: ", 31);
	(void)write(2, &command.str[exp.offset], exp.size);
	(void)write(2, "\n", 1);
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
