/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:01:02 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:01:02 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <assert.h>
#include "ft_printf.h"
#include "errors.h"
#include "shell.h"

static char		*g_context;

void	error_print(const char *module_name)
{
	assert(module_name != NULL);
	assert(g_context != NULL);
	ft_dprintf(2, BIN_NAME ": %s: %s\n", module_name, g_context);
	free(g_context);
	g_context = NULL;
}

void	error_set_context(const char *format, ...)
{
	va_list	args;

	assert(format != NULL);
	free(g_context);
	va_start(args, format);
	ft_vasprintf(&g_context, format, args);
	va_end(args);
}
