#include "user_interface.h"

void	ui_leave(t_editenv *e)
{
	if (e->entry.len == 0)
		e->must_leave = true;
}

void	ui_arg_num(t_editenv *e)
{
	if (FT_ISDIGIT(e->rbuff.str[e->rbuff_index]))
	{
		e->arg_num += e->rbuff.str[e->rbuff_index] - '0';
		e->arg_num *= 10;
	}
}

void	ui_change_case(t_editenv *e)
{
	int arg_num;

	arg_num = 0;
	if (e->arg_num > 0)
		arg_num = e->arg_num;
	else
		arg_num = (int)(e->entry.len - e->entry_index);
	while (arg_num-- && e->entry_index < e->entry.len)
	{
		if (FT_ISLOWER(e->entry.str[e->entry_index]))
			e->entry.str[e->entry_index] =
				FT_TOUPPER(e->entry.str[e->entry_index]);
		else if (FT_ISUPPER(e->entry.str[e->entry_index]))
			e->entry.str[e->entry_index] =
				FT_TOLOWER(e->entry.str[e->entry_index]);
		if (e->entry_index >= e->entry.len - 1)
			break ;
		e->entry_index++;
	}
	e->arg_num = -1;
}

void	ui_move_to_first_non_blank(t_editenv *e)
{
	e->entry_index = 0;
	while (e->entry_index < e->entry.len)
	{
		if (e->entry.str[e->entry_index] != ' ')
			return ;
		e->entry_index++;
	}
}

void	ui_clear(t_editenv *e)
{
	(void)e;
	term_command("cl");
	prompt(e->prompt);
}
