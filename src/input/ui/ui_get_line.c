#include "input.h"
#include "errors.h"
#include "terminal.h"
#include "user_interface.h"
#include "ft_printf.h"

bool	g_is_eof = false;

static void	update_term_env(t_term_env *env)
{
	if (env->autocomplete_state == E_LAST_CMD_REALLY_WAS_AUTOCOMPLETE)
		env->autocomplete_state = E_LAST_CMD_WAS_AUTOCOMPLETE;
	else if (env->autocomplete_state == E_LAST_CMD_WAS_AUTOCOMPLETE)
		env->autocomplete_state = E_NO_AUTOCOMPLETE;
	term_env_update_for_resize(env);
}

static int	ui_read_line(t_term_env *env)
{
	ssize_t				ret;
	char				c;
	t_input_sequence	s;

	s.len = 0;
	while (!g_is_eof)
	{
		terminal_start_raw_mode();
		ret = read(0, &c, 1);
		terminal_stop_raw_mode();
		if (ret == 0)
			break ;
		else if (ret == -1 && errno == EINTR)
			return (CMD_DROP_);
		if ((c == E_CTRL_J || c == E_CTRL_M || c == E_ENTER) && s.len == 0)
			return (OK_);
		else if (c == E_CTRL_D && s.len == 0 && env->line.str->len == 0)
			break ;
		s.data[s.len] = c;
		s.len += 1;
		update_term_env(env);
		input_sequence_handle(&s, env);
	}
	g_is_eof = true;
	return (CMD_EOF_);
}

int			input_ui_get_line(t_string *line, const char *prompt)
{
	t_term_env			env;
	int					status;

	if (g_is_eof)
		return (CMD_EOF_);
	ft_printf(prompt);
	init_term_env(&env, line, prompt);
	status = ui_read_line(&env);
	ui_handler_jump_end(&env, '\0');
	ft_printf("\n");
	if (status == OK_)
		fatal_malloc(string_ncat(line, "\n", 1));
	if (status == ERROR_)
		error_set_context("read : %s", strerror(errno));
	shutdown_term_env(&env);
	return (status);
}
