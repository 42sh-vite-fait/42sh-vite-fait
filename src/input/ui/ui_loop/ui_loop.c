#include <stdio.h>
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
	char				buff[MEM_PAGE_SIZE];
	ssize_t				ret;

	ret = read(0, buff, MEM_PAGE_SIZE);
	if (ret < 0)
		return ;
	if (ret == 0)
	{
		e->must_leave = true;
		return ;
	}
	string_insert(&e->rbuff, 0, buff, (size_t)ret);
}

static void		compute_user_entry(t_editenv *e)
{
	static t_string		mem_buff = { .str = NULL, .len = 0 };

	if (mem_buff.str == NULL)
		string_init(&mem_buff);
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

static void		init(t_editenv *e, t_string *cpy)
{
	static bool first_init = false;

	ft_memset(e, 0, sizeof(t_editenv));
	string_init(&e->entry);
	string_init(&e->initial_entry);
	if (!first_init)
	{
		string_init(&e->rbuff);
		string_init(&e->cpy);
	}
	else
		e->cpy = *cpy;
	e->entry_index = 0;
	e->selection_size = 1;
	e->cpos.x = (int)(prompt());
	term_mode();
	ui_display_user_entry(e);
	first_init = true;
}

t_string			ui_get_user_input(void)
{
	t_editenv			e;
	char				*output;
	static t_string		cpy_buffer_mem;
	ssize_t				offset_nl;
	t_string			ret;

	normal_mode();
	init(&e, &cpy_buffer_mem);
	output = NULL;
	while ((offset_nl = ft_strchrpos(e.entry.str, '\n')) == -1 && !e.must_leave)
	{
		compute_user_entry(&e);
		ui_display_user_entry(&e);
	}
	if (!e.must_leave)
	{
		output= ft_strsub(e.entry.str, 0, (size_t)offset_nl + 1);
		cpy_buffer_mem = e.cpy;
	}
	normal_mode();
	free_data(&e);
	string_init(&ret);
	if (output != NULL)
		string_insert(&ret, 0, output, ft_strlen(output));
	else
		ret.str = NULL;
	return (ret);
}
