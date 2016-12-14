#include "user_interface.h"

void	ui_handler_move_right_word(t_editenv *e)
{
	size_t	i;
	bool	is_word;

	e->is_selecting = false;
	e->selection_size = 1;
	is_word = false;
	i = e->entry_index;
	while (i < e->entry.len)
	{
		if (e->entry.str[i] < '!' || e->entry.str[i] > '~')
			is_word = true;
		if (is_word && e->entry.str[i] >= '!' && e->entry.str[i] <= '~')
		{
			e->entry_index = i;
			break ;
		}
		i++;
	}
}

void	ui_handler_move_right_char(t_editenv *e)
{
	if (e->entry_index < e->entry.len)
	{
		if (!e->is_selecting)
			e->entry_index++;
		else if (e->entry_index + e->selection_size < e->entry.len)
			e->selection_size++;
	}
}

void	ui_handler_move_end(t_editenv *e)
{
	e->entry_index = e->entry.len;
	e->selection_size = 1;
	e->is_selecting = false;
}
