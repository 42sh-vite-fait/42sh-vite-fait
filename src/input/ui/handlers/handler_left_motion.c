#include "user_interface.h"

void	ui_handler_move_left_word(t_editenv *e)
{
	ssize_t	i;
	bool	is_word;

	e->is_selecting = false;
	e->selection_size = 1;
	is_word = false;
	i = e->entry_index;
	while (i >= 0)
	{
		if (e->entry.str[i] < '!' || e->entry.str[i] > '~')
			is_word = true;
		if (is_word && e->entry.str[i] >= '!' && e->entry.str[i] <= '~')
		{
			e->entry_index = i;
			break ;
		}
		i--;
	}
}

void	ui_handler_move_left_char(t_editenv *e)
{
	if (e->entry_index > 0 || e->is_selecting)
	{
		if (!e->is_selecting)
			e->entry_index--;
		if (e->selection_size > 1)
			e->selection_size--;
		else
		{
			e->is_selecting = false;
			e->selection_size = 1;
		}
	}
}

void	ui_handler_move_home(t_editenv *e)
{
	e->entry_index = 0;
	e->selection_size = 1;
	e->is_selecting = false;
}
