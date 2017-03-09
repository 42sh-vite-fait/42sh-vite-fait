#include "ctype_42.h"
#include "history.h"
#include "var.h"

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

void			shell_history_init(void)
{
	const char	*hist_size_str;
	int			status;
	size_t		hist_size;
	const char	*hist_file;
	const char	*home;
	t_string	default_hist_file;

	status = var_get("HISTSIZE", &hist_size_str);
	if (status == NO_ERROR && hist_size_str != NULL)
	{
		hist_size = atou(hist_size_str);
		if (hist_size > HIST_MAX_SIZE)
			hist_size = HIST_DEFAULT_SIZE;
	}
	else
		hist_size = HIST_DEFAULT_SIZE;
	history_init(hist_size); // fatal_malloc in history_init

	status = var_get("HISTFILE", &hist_file);
	if (status == NO_ERROR && hist_file != NULL
		&& history_load_from_file(hist_file) == 0)
		return ;

	status = var_get("HOME", &home);
	if (status == NO_ERROR && home != NULL)
	{
		string_init_dup(&default_hist_file, home); // fatal_malloc
		string_cat(&default_hist_file, HIST_DEFAULT_FILE); // fatal_malloc
		history_load_from_file(default_hist_file.str);
	}
}

void			shell_history_shutdown(void)
{
	int			status;
	const char	*hist_file;
	const char	*home;
	t_string	default_hist_file;

	status = var_get("HISTFILE", &hist_file);
	if (status == NO_ERROR && hist_file != NULL
		&& history_save_into_file(hist_file) == 0)
		return ;
	status = var_get("HOME", &home);
	if (status == NO_ERROR && home != NULL)
	{
		fatal_malloc(string_init_dup(&default_hist_file, home));
		fatal_malloc(string_cat(&default_hist_file, HIST_DEFAULT_FILE));
		history_save_into_file(default_hist_file.str);
	}
}
