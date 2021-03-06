/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:38:03 by djean             #+#    #+#             */
/*   Updated: 2017/04/02 12:48:20 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_42.h"
#include "ft_printf.h"
#include "shell.h"
#include "lexer.h"
#include "opt.h"
#include "input.h"
#include "sig.h"
#include "expansion.h"

int	shell_input(t_string *line, const char *prompt)
{
	int			ret;
	bool		is_line_complete;
	t_string	current_line;

	is_line_complete = false;
	fatal_malloc(string_init(&current_line));
	while (!is_line_complete)
	{
		ret = input_get_line(&current_line, prompt);
		if (ret == OK_ && expand_history(&current_line) == ERROR_)
			ret = CMD_DROP_;
		if (ret != OK_)
			break ;
		fatal_malloc(string_append(line, &current_line));
		if (remove_escaped_newline(line) == LINE_COMPLETE)
			is_line_complete = true;
		string_truncate(&current_line, 0);
		prompt = SHELL_PS2;
	}
	if (ret == CMD_EOF_ && line->len != 0)
		ret = OK_;
	string_shutdown(&current_line);
	return (ret);
}
