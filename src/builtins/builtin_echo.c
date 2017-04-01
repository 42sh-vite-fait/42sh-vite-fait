/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 19:53:31 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 19:53:32 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "string_42.h"
#include "str_42.h"
#include "error_42.h"
#include "ft_printf.h"
#include "builtins.h"

static void	concat_args(t_string *buf, const char *const *argv)
{
	while (*argv)
	{
		fatal_malloc(string_cat(buf, *argv));
		if (argv[1] != NULL)
			fatal_malloc(string_ncat(buf, " ", 1));
		argv += 1;
	}
}

int			builtin_echo(int argc, const char *const *argv)
{
	t_string	buf;
	bool		newline;

	fatal_malloc(string_init(&buf));
	argv += 1;
	newline = true;
	if (*argv != NULL && ft_strcmp(*argv, "-n") == 0)
	{
		newline = false;
		argv += 1;
	}
	if (argc > 1)
		concat_args(&buf, argv);
	if (newline)
		fatal_malloc(string_ncat(&buf, "\n", 1));
	ft_printf("%s", buf.str);
	string_shutdown(&buf);
	return (0);
}
