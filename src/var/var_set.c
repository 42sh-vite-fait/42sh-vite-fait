/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:41:00 by djean             #+#    #+#             */
/*   Updated: 2017/04/02 15:32:42 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "str_42.h"
#include "array_42.h"
#include "ft_printf.h"
#include "var.h"
#include "errors.h"
#include "misc.h"

extern t_array	g_environ;

static ssize_t	get_entry_index(const char *name, size_t name_len)
{
	char	*entry;
	size_t	i;

	i = 0;
	while (i < g_environ.len)
	{
		entry = *(char**)array_get_at(&g_environ, i);
		if (entry == NULL)
			break ;
		if (!ft_strncmp(entry, name, name_len) && entry[name_len] == '=')
			return (i);
		i += 1;
	}
	return (-1);
}

int				var_set(const char *name, const char *value)
{
	void	*old_entry;
	char	*new_entry;
	ssize_t	old_entry_index;
	size_t	name_len;

	name_len = ft_strlen(name);
	assert(is_valid_name(name, name_len));
	if (ft_asprintf(&new_entry, "%s=%s", name, value) == -1)
		fatal_malloc(new_entry);
	old_entry_index = get_entry_index(name, name_len);
	if (old_entry_index != -1)
	{
		array_replace_at(&g_environ, old_entry_index, &new_entry, &old_entry);
		free(old_entry);
	}
	else
		fatal_malloc(array_insert_at(&g_environ,
					g_environ.len - 1, &new_entry));
	return (OK_);
}

int				var_unset(const char *name)
{
	void	*removed_entry;
	ssize_t	removed_entry_index;
	size_t	name_len;

	name_len = ft_strlen(name);
	assert(is_valid_name(name, name_len));
	removed_entry_index = get_entry_index(name, name_len);
	if (removed_entry_index == -1)
		return (ERROR_);
	array_remove_at(&g_environ, removed_entry_index, &removed_entry);
	free(removed_entry);
	return (OK_);
}
