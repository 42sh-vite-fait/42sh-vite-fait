#include "user_interface.h"

void	ui_handler_move_down(t_editenv *e)
{
	size_t cols;

	cols = (size_t)get_cols();
	if (e->entry.len - e->entry_index < cols)
	{
		if (!e->is_selecting)
			e->entry_index = e->entry.len;
		else
			e->selection_size = e->entry.len - e->entry_index;
	}
	else
	{
		if (!e->is_selecting)
			e->entry_index += cols;
		else if (e->entry.len - (e->entry_index + e->selection_size) > cols)
			e->selection_size += cols;
		else
			e->selection_size += e->entry.len - (e->entry_index +
				e->selection_size);
	}
}

void	ui_handler_move_up(t_editenv *e)
{
	size_t cols;

	cols = (size_t)get_cols();
	if (e->entry_index > cols)
	{
		e->entry_index -= cols;
		if (e->is_selecting)
			e->selection_size += cols;
		if (e->selection_size + e->entry_index > e->entry.len)
			e->selection_size -= 1;
	}
	else
	{
		if (!e->is_selecting)
			e->entry_index = 0;
		else
		{
			e->selection_size += e->entry_index;
			e->entry_index = 0;
			if (e->selection_size > e->entry.len)
				e->selection_size -= 1;
		}
	}
}
