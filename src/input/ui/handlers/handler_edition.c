#include "user_interface.h"

void	ui_handler_do_nothing(t_editenv *e)
{
	(void)e;
}

void	ui_handler_valid_line(t_editenv *e)
{
	string_insert(&e->entry, e->entry.len,
					&(e->rbuff.str[e->rbuff_index]), 1);
	e->entry_index++;
}

void	ui_handler_insert_char(t_editenv *e)
{
	if (e->is_selecting)
	{
		string_remove(&e->entry, e->entry_index, e->selection_size);
		e->is_selecting = 0;
		e->selection_size = 1;
	}
	string_insert(&e->entry, e->entry_index,
					&(e->rbuff.str[e->rbuff_index]), 1);
	e->entry_index++;
}
