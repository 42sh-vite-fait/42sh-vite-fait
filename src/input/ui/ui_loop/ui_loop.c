#include <stdio.h>
#include <errno.h>
#include "input.h"
#include "user_interface.h"
#include "str_42.h"

static void		free_data(t_editenv *e)
{
	string_shutdown(&e->entry);
	string_shutdown(&e->initial_entry);
	if (e->must_leave)
	{
		string_shutdown(&e->cpy);
		string_shutdown(&e->rbuff);
	}
}

static void		read_input(t_editenv *e)
{
	char	c;
	ssize_t	ret;

	ret = read(0, &c, 1);
	if (ret <= 0)
	{
		if (ret < 0)
		{
			error_set_context("read: %s.", strerror(errno));
			error_print("input");
		}
		e->must_leave = true;
		return ;
	}
	fatal_malloc(string_insert(&e->rbuff, 0, &c, (size_t)ret));
}

static void		compute_user_entry(t_editenv *e)
{
	static t_string		mem_buff = { .str = NULL, .len = 0 };

	if (mem_buff.str == NULL)
		fatal_malloc(string_init(&mem_buff));
	e->rbuff = mem_buff;
	e->rbuff_index = 0;
	if (e->rbuff.len == 0)
		read_input(e);
	while (e->rbuff_index < e->rbuff.len && !ft_strchr(e->entry.str, '\n'))
	{
		ui_execute_handler(e);
		e->rbuff_index++;
	}
	string_remove(&e->rbuff, 0, e->rbuff_index);
	mem_buff = e->rbuff;
}

static int		init(t_editenv *e, t_string *cpy, const char *p)
{
	static bool first_init = false;

	ft_memset(e, 0, sizeof(t_editenv));
	fatal_malloc(string_init(&e->entry));
	fatal_malloc(string_init(&e->initial_entry));
	if (!first_init)
	{
		fatal_malloc(string_init(&e->rbuff));
		fatal_malloc(string_init(&e->cpy));
	}
	else
		e->cpy = *cpy;
	e->history_index = 0;
	e->entry_index = 0;
	e->selection_size = 1;
	e->cpos.x = (int)(prompt(p));
	if (terminal_start_raw_mode() != NO_ERROR) 
		return (ERR_TERM); 
	e->prompt = p;
	ui_display_user_entry(e);
	first_init = true;
	return (NO_ERROR);
}

int				ui_get_user_input(t_string *input, const char *prompt)
{
	t_editenv			e;
	static t_string		cpy_buffer_mem;
	ssize_t				offset_nl;
	int					ret;

	if (init(&e, &cpy_buffer_mem, prompt) != NO_ERROR)
		exit(0);
		//		return (E_INPUT_ERROR);
	while ((offset_nl = ft_strchrpos(e.entry.str, '\n')) == -1 && !e.must_leave)
	{
		compute_user_entry(&e);
		ui_display_user_entry(&e);
	}
	if (!e.must_leave)
	{
		fatal_malloc(string_ncat(input, e.entry.str, offset_nl + 1));
		cpy_buffer_mem = e.cpy;
		ret = E_INPUT_OK;
	}
	else
		ret = E_INPUT_EOF;
	if (terminal_stop_raw_mode() != NO_ERROR) 
		ret = E_INPUT_ERROR; 
	free_data(&e);
	return (ret);
}
