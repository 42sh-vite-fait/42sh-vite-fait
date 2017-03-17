#include "user_interface.h"
#include "terminal.h"

int		line_move_offset_x(t_term_line *line, int move)
{
	int		term_cols;
	int		vec_x;
	int		dst_x;

	term_cols = line->term_x;
	dst_x = (line->cursor_x + move) % term_cols;
	dst_x = (dst_x + term_cols) % term_cols;
	vec_x = dst_x - line->cursor_x;
	return (vec_x);
}

int		line_move_offset_y(t_term_line *line, int move)
{
	int		term_cols;
	int		vec_y;

	term_cols = line->term_x;
	vec_y = (line->cursor_x + move);
	if (vec_y < 0)
		vec_y -= term_cols - 1;
	vec_y /= term_cols;
	return (vec_y);
}

void	line_move_cursor(t_term_line *line, int move)
{
	int		vec_x;
	int		vec_y;

	vec_x = line_move_offset_x(line, move);
	vec_y = line_move_offset_y(line, move);
	if (vec_x < 0)
		terminal_move_cursor(CAPS_CURSOR_LEFT, -vec_x);
	else if (vec_x > 0)
		terminal_move_cursor(CAPS_CURSOR_RIGHT, vec_x);
	if (vec_y < 0)
		terminal_move_cursor(CAPS_CURSOR_UP, -vec_y);
	else if (vec_y > 0)
		terminal_move_cursor(CAPS_CURSOR_DOWN, vec_y);
	line->cursor_x += vec_x;
}
