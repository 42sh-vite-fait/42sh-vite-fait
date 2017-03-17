#include "ctype_42.h"
#include "terminal.h"
#include "user_interface.h"

void	ui_handler_move_right(t_term_env *env, char c)
{
	(void)c;
	if (env->line.string_index >= env->line.str->len)
		return ;
	line_move_cursor(&env->line, 1);
	env->line.string_index += 1;
}

void	ui_handler_move_left(t_term_env *env, char c)
{
	(void)c;
	if (env->line.string_index == 0)
		return ;
	line_move_cursor(&env->line, -1);
	env->line.string_index -= 1;
}

void	ui_handler_move_up(t_term_env *env, char c)
{
	int	offset;

	(void)c;
	offset = (int)FT_MIN(env->line.term_x, env->line.string_index);
	if (offset == 0)
		return ;
	line_move_cursor(&env->line, -offset);
	env->line.string_index -= offset;
}

void	ui_handler_move_down(t_term_env *env, char c)
{
	int	offset;

	(void)c;
	offset = (int)FT_MIN(env->line.term_x,
						env->line.str->len - env->line.string_index);
	if (offset == 0)
		return ;
	line_move_cursor(&env->line, offset);
	env->line.string_index += offset;
}
