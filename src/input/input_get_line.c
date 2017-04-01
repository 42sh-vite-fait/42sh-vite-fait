/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_get_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:19:58 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:20:24 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_42.h"
#include "input.h"
#include "errors.h"
#include "opt.h"
#include "sig.h"

static int	input_arg_get_line(t_string *line)
{
	const char		*arg;
	size_t			arglen;
	static size_t	index = 0;
	ssize_t			next_newline;

	arg = opt_get_command_line() + index;
	arglen = ft_strlen(arg);
	if (arg[0] == '\0')
		return (CMD_EOF_);
	next_newline = ft_strchrpos(arg, '\n');
	if (next_newline == -1)
	{
		fatal_malloc(string_ncat(line, arg, arglen));
		index += arglen;
	}
	else
	{
		next_newline += 1;
		fatal_malloc(string_ncat(line, arg, next_newline));
		index += next_newline;
	}
	return (OK_);
}

static int	input_notty_get_line(t_string *line)
{
	ssize_t	ret;
	char	c;

	while ((ret = read(STDIN_FILENO, &c, 1)) > 0)
	{
		if (c == '\0')
			continue ;
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

int			input_get_line(t_string *line, const char *prompt)
{
	int			ret;

	if (opt_is_set(OPT_CMD_STRING))
		ret = input_arg_get_line(line);
	else if (opt_is_set(OPT_INTERACTIVE))
	{
		signal_set_input_context(); // TODO syscall might be stopped
		ret = input_ui_get_line(line, prompt);
		signal_set_post_input_context();
	}
	else
		ret = input_notty_get_line(line);
	if (ret == ERROR_)
		error_print("input");
	return (ret);
}
