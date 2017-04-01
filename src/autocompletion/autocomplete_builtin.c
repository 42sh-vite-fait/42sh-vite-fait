/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_builtin.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 19:52:30 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 19:52:32 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_42.h"
#include "builtins.h"
#include "autocompletion.h"

extern const size_t			g_builtins_len;
extern t_pair_name_builtin	g_builtins[];

void	complete_builtin(t_array *matches, const char *name)
{
	size_t						builtin_id;
	char						*match;
	const t_pair_name_builtin	*cur_builtin;
	size_t						cmd_len;

	cmd_len = ft_strlen(name);
	builtin_id = 0;
	cur_builtin = g_builtins;
	while (builtin_id < g_builtins_len)
	{
		if (ft_strncmp(name, cur_builtin->name, cmd_len) == 0)
		{
			match = fatal_malloc(ft_strdup(cur_builtin->name));
			fatal_malloc(array_push(matches, &match));
		}
		cur_builtin += 1;
		builtin_id += 1;
	}
}
