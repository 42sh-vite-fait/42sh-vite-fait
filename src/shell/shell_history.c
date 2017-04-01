#include "ctype_42.h"
#include "history.h"
#include "var.h"
#include "shell.h"
#include "opt.h"

static size_t	atou(const char *str)
{
	size_t		ret;

	ret = 0;
	while (*str && FT_ISDIGIT(*str))
	{
		ret = ret * 10 + (*str - '0');
		str += 1;
	}
	if (*str != '\0')
		return (0);
	return (ret);
}

static void		history_file_action(int (*action)(const char*))
{
	const char	*hist_file;
	const char	*home;
	t_string	default_hist_file;
	int			status;

	status = var_get("HISTFILE", &hist_file);
	if (status == OK_ && hist_file != NULL
		&& action(hist_file) == 0)
		return ;
	status = var_get("HOME", &home);
	if (status == OK_ && home != NULL)
	{
		fatal_malloc(string_init_dup(&default_hist_file, home));
		fatal_malloc(string_cat(&default_hist_file, HIST_DEFAULT_FILE));
		action(default_hist_file.str);
		string_shutdown(&default_hist_file);
	}
}

void			shell_history_init(void)
{
	const char	*hist_size_str;
	int			status;
	size_t		hist_size;

	status = var_get("HISTSIZE", &hist_size_str);
	if (status == OK_ && hist_size_str != NULL)
	{
		hist_size = atou(hist_size_str);
		if (hist_size > HIST_MAX_SIZE)
			hist_size = HIST_DEFAULT_SIZE;
	}
	else
		hist_size = HIST_DEFAULT_SIZE;
	history_init(hist_size);
	if (opt_is_set(OPT_INTERACTIVE))
		history_file_action(history_load_from_file);
}

void			shell_history_shutdown(void)
{
	if (opt_is_set(OPT_INTERACTIVE))
		history_file_action(history_save_into_file);
}
