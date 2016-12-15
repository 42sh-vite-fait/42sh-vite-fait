#include "user_interface.h"

void	ui_handler_up_history(t_editenv *e)
{
	e->is_selecting = 0;
	e->selection_size = 1;
	e->entry_index = 0;

	if (e->history_index == 0)
	{
		free(e->initial_entry.str);
		string_init_dup(&e->initial_entry, e->entry.str);
	}
	if (history_get_last_id() > (size_t)e->history_index)
	{
		e->history_index++;
		free(e->entry.str);
		string_init_dup(&e->entry, history_get(history_get_last_id() - e->history_index + 1)->str);
	}
}

void	ui_handler_down_history(t_editenv *e)
{
	e->is_selecting = 0;
	e->selection_size = 1;
	e->entry_index = 0;

	if (e->history_index > 1)
	{
		e->history_index--;
		free(e->entry.str);
		string_init_dup(&e->entry, history_get(history_get_last_id() - e->history_index + 1)->str);
	}
	else
	{
		e->history_index = 0;
		free(e->entry.str);
		string_init_dup(&e->entry, e->initial_entry.str);
	}
}
