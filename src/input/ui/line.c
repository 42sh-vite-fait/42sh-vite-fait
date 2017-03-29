#include "user_interface.h"
#include "ft_printf.h"
#include "terminal.h"

void	line_print(t_term_line *line)
{
	int			write_len;
	t_string	to_print;
	ssize_t		pos;

	write_len = (int)(line->str->len - line->string_index);
	if (write_len == 0)
		return ;
	string_init_dup(&to_print, line->str->str + line->string_index);
	while ((pos = ft_strchrpos(to_print.str, '\n')) != -1)
	{
		string_remove(&to_print, pos, 1);
		string_insert(&to_print, pos, "␤", sizeof("␤") - 1);
	}
	ft_printf(to_print.str);
	line->cursor_x += line_move_offset_x(line, write_len);
	if (line->cursor_x == 0)
	{
		ft_printf(" ");
		terminal_move_cursor(CAPS_CURSOR_LEFT, 1);
	}
	line_move_cursor(line, -write_len);
	string_shutdown(&to_print);
}

void	line_insert(t_term_line *line, const char *s, size_t len)
{
	string_insert(line->str, line->string_index, s, len);
	line_print(line);
	line_move_cursor(line, (int)len);
	line->string_index += len;
}

void	line_replace(t_term_line *line, const char *new_str, size_t new_str_len)
{
	string_truncate(line->str, 0);
	line_move_cursor(line, -(int)line->string_index);
	line->string_index = 0;
	terminal_execute_caps(CAPS_CLEAR_EOS);
	line_insert(line, new_str, new_str_len);
}

void	line_remove_left(t_term_line *line, size_t removed_len)
{
	string_remove(line->str, line->string_index - removed_len, removed_len);
	line->string_index -= removed_len;
	line_move_cursor(line, -(int)removed_len);
	terminal_execute_caps(CAPS_CLEAR_EOS);
	line_print(line);
}

void	line_remove_right(t_term_line *line, size_t removed_len)
{
	string_remove(line->str, line->string_index, removed_len);
	terminal_execute_caps(CAPS_CLEAR_EOS);
	line_print(line);
}
