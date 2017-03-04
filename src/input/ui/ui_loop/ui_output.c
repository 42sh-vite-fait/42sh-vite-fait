#include <user_interface.h>

static void		reverse_video_mode(char *str)
{
	if (!ft_strchr(str, '\n'))
		term_toggle_video_mode();
}

static void		replace_cursor(size_t xpos, size_t lenline)
{
	size_t			xflat;
	ssize_t			to_move;

	xpos %= get_cols();
	if (xpos + lenline != 0)
	{
		to_move = (xpos + lenline) / get_cols();
		while (to_move)
		{
			term_command("up");
			to_move--;
		}
	}
	xflat = (xpos + lenline) % get_cols();
	to_move = -(xpos - xflat);
	while (to_move)
	{
		if (to_move > 0)
			term_command("le");
		else
			term_command("nd");
		to_move += to_move > 0 ? -1 : 1;
	}
}

static void		write_entry(char *str, size_t len, size_t xpos,
	size_t *writen_before)
{
	size_t			writen;
	size_t			to_write;

	writen = 0;
	xpos %= get_cols();
	while ((ssize_t)len > 0)
	{
		to_write = get_cols() - ((xpos + writen +
			*writen_before) % (size_t)get_cols());
		if (to_write > len)
			to_write = len;
		(void)write(1, str, to_write);
		writen += to_write;
		str += to_write;
		len -= to_write;
		if (((xpos + writen + *writen_before) % (size_t)get_cols()) == 0)
			(void)write(1, "\n\r", 2);
	}
	*writen_before += writen;
}

void			ui_display_user_entry(t_editenv *e)
{
	size_t		writen;
	bool		cur_emulated_pad;

	cur_emulated_pad = e->entry_index == e->entry.len ? true : false;
	if (cur_emulated_pad)
		string_insert(&e->entry, e->entry.len, " ", 1);
	writen = 0;
	term_clear_bottom();
	write_entry(e->entry.str, e->entry_index, (e->cpos.x), &writen);
	reverse_video_mode(e->entry.str);
	if (e->entry_index < e->entry.len)
		write_entry(e->entry.str + e->entry_index, e->selection_size,
			(e->cpos.x), &writen);
	reverse_video_mode(e->entry.str);
	if (e->entry.len > e->entry_index + e->selection_size)
		write_entry(e->entry.str + e->entry_index + e->selection_size,
			e->entry.len - (e->selection_size + e->entry_index),
			(e->cpos.x), &writen);
	if (!ft_strchr(e->entry.str, '\n'))
		replace_cursor(e->cpos.x, e->entry.len);
	if (cur_emulated_pad)
		string_remove(&e->entry, e->entry_index, 1);
	if (ft_strchr(e->entry.str, '\n'))
		(void)write(1, "\r", 1);
}
