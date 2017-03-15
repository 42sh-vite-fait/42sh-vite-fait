#include "user_interface.h"

void	ui_handler_copy(t_editenv *e)
{
	if (e->is_selecting && e->entry_index < e->entry.len)
	{
		fatal_malloc(string_nreplace(&e->cpy, e->entry.str + e->entry_index,
						e->selection_size));
	}
}

void	ui_handler_cut(t_editenv *e)
{
	ui_handler_copy(e);
	if (e->is_selecting && e->entry_index < e->entry.len)
	{
		string_remove(&e->entry, e->entry_index, e->selection_size);
		e->is_selecting = false;
		e->selection_size = 1;
	}
}

void	ui_handler_paste(t_editenv *e)
{
		fatal_malloc(string_insert(&e->entry, e->entry_index, e->cpy.str, e->cpy.len));
}

void	ui_handler_visual_selection(t_editenv *e)
{
	if (!e->is_selecting)
	{
		e->is_selecting = true;
	}
	else
	{
		e->is_selecting = false;
		e->selection_size = 1;
	}
}
