/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_scanning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:22:42 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:22:46 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <unistd.h>
#include <sys/stat.h>
#include "string_42.h"
#include "misc.h"

static ssize_t	get_next_path_len(const char *paths)
{
	ssize_t	len;

	if (*paths == '\0')
		return (-1);
	len = ft_strchrpos(paths, ':');
	if (len == -1)
		return (ft_strlen(paths));
	else
		return (len);
}

bool			is_dir(const char *file)
{
	struct stat	file_stat;

	return (stat(file, &file_stat) == 0 &&
			S_ISDIR(file_stat.st_mode));
}

const char		*get_next_path(t_string *str, char const *paths)
{
	ssize_t		len;

	assert(str != NULL && paths != NULL);
	if ((len = get_next_path_len(paths)) < 0)
		return (NULL);
	string_truncate(str, 0);
	fatal_malloc(string_reserve(str, len + 2));
	if (len == 0)
		string_nreplace(str, "./", 2);
	else
		string_nreplace(str, paths, len);
	paths += len;
	if (paths[0] == ':' && !(paths[1] == '\0' && len != 0))
		paths += 1;
	if (str->str[str->len - 1] != '/')
		string_cat(str, "/");
	return (paths);
}
