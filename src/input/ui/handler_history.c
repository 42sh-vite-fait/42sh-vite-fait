#include "user_interface.h"

void	ui_handler_up_history(t_editenv *e)
{
	const t_string	*history_entry;

	e->is_selecting = 0;
	e->selection_size = 1;
	e->entry_index = 0;
	history_entry = history_get(history_get_last_id() - e->history_index);
	if (history_entry != NULL)
	{
		e->history_index += 1;
		fatal_malloc(string_nreplace(&e->entry, history_entry->str, history_entry->len));
	}
}

void	ui_handler_down_history(t_editenv *e)
{
	const t_string	*history_entry;

	e->is_selecting = 0;
	e->selection_size = 1;
	e->entry_index = 0;
	if (e->history_index > 1)
	{
		history_entry = history_get(history_get_last_id() - e->history_index + 2);
		if (history_entry != NULL)
		{
			e->history_index -= 1;
			fatal_malloc(string_nreplace(&e->entry, history_entry->str, history_entry->len));
		}
	}
	else if (e->history_index == 1)
	{
		fatal_malloc(string_nreplace(&e->entry, e->initial_entry.str, e->initial_entry.len));
		e->history_index = 0;
	}
	else
		fatal_malloc(string_nreplace(&e->entry, e->initial_entry.str, e->initial_entry.len));
}
