#include <assert.h>
#include "str_42.h"
#include "input.h"
#include "errors.h"
#include "opt.h"

static int	input_arg_get_line(t_string *line)
{
	const char		*arg;
	static size_t	index = 0;
	ssize_t			offset;

	arg = opt_get_command_line();
	assert(arg != NULL);
	if (arg[index] == '\0')
		return (CMD_EOF_);
	offset = ft_strchrpos(arg + index, '\n');
	if (offset == -1)
	{
		fatal_malloc(string_cat(line, arg + index));
		index += ft_strlen(arg);
	}
	else
	{
		offset += 1;
		fatal_malloc(string_ncat(line, arg + index, offset));
		index += offset;
	}
	return (OK_);
}

static int	input_notty_get_line(t_string *line)
{
	ssize_t	ret;
	char	c;

	while ((ret = read(STDIN_FILENO, &c, 1)) > 0)
	{
		fatal_malloc(string_ncat(line, &c, 1));
		if (c == '\n')
			break ;
	}
	if (ret == -1)
	{
		error_set_context("read: %s", strerror(errno));
		return (ERROR_);
	}
	else if (ret == 0 && line->len == 0)
		return (CMD_EOF_);
	else
		return (OK_);
}

int	input_get_line(t_string *line, const char *prompt)
{
	int			ret;

	if (opt_is_set(OPT_CMD_STRING))
		ret = input_arg_get_line(line);
	else if (opt_is_set(OPT_INTERACTIVE))
		ret = input_ui_get_line(line, prompt);
	else
		ret = input_notty_get_line(line);
	if (ret == ERROR_)
		error_print("input");
	return (ret);
}
