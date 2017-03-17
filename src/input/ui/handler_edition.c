#include "user_interface.h"

void		ui_handler_do_nothing(t_term_env *env, char c)
{
	(void)c;
	(void)env;
}

void		ui_handler_delete_left(t_term_env *env, char c)
{
	(void)c;
	if (env->line.string_index > 0)
		line_remove_left(&env->line, 1);
}

void		ui_handler_delete_right(t_term_env *env, char c)
{
	(void)c;
	if (env->line.string_index < env->line.str->len)
		line_remove_right(&env->line, 1);
}

void		ui_handler_insert_char(t_term_env *env, char c)
{
	line_insert(&env->line, &c, 1);
}
