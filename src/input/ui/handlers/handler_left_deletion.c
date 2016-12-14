#include "user_interface.h"

void	ui_handler_delete_left_char(t_editenv *e)
{
	if (e->is_selecting)
	{
		string_remove(&e->entry, e->entry_index, e->selection_size);
		e->is_selecting = false;
		e->selection_size = 1;
	}
	else if (e->entry_index > 0)
	{
		string_remove(&e->entry, e->entry_index - 1, 1);
		e->entry_index -= 1;
	}
}

void	ui_handler_delete_left_word(t_editenv *e)
{
	(void)e;
}

void	ui_handler_delete_left_begin(t_editenv *e)
{
	(void)e;
}
