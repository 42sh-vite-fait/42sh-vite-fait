#include <errno.h>
#include "input.h"
#include "user_interface.h"
#include "errors.h"
#include "lexer.h"
#include "shell.h"

static int	input_arg_get_line(t_string *input)
{
	const char		*arg;
	static size_t	index = 0;
	ssize_t			offset;

	arg = opt_get_command_line();
	assert(arg != NULL);
	if (arg[index] == '\0')
		return (E_INPUT_EOF);
	offset = ft_strchrpos(arg + index, '\n');
	if (offset == -1)
	{
		fatal_malloc(string_cat(input, arg + index));
		index += ft_strlen(arg);
	}
	else
	{
		offset += 1;
		fatal_malloc(string_ncat(input, arg + index, offset));
		index += offset;
	}
	return (E_INPUT_OK);
}

static int	input_notty_get_line(t_string *input)
{
	ssize_t	ret;
	char	c;

	while ((ret = read(STDIN_FILENO, &c, 1)) > 0)
	{
		fatal_malloc(string_ncat(input, &c, 1));
		if (c == '\n')
			break ;
	}
	if (ret == -1)
	{
		error_set_context("read: %s", strerror(errno));
		return (E_INPUT_ERROR);
	}
	else if (ret == 0 && input->len == 0)
		return (E_INPUT_EOF);
	else
		return (E_INPUT_OK);
}

int	input_get_line(t_string *input, const char *prompt)
{
	int			ret;

	if (opt_is_set(OPT_CMD_STRING))
		ret = input_arg_get_line(input);
	else if (opt_is_set(OPT_INTERACTIVE))
		ret = ui_get_user_input(input, prompt);
	else
		ret = input_notty_get_line(input);
	if (ret == E_INPUT_ERROR)
		error_print("input");
	return (ret);
}
