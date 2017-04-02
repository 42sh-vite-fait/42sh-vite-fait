/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 19:53:23 by djean             #+#    #+#             */
/*   Updated: 2017/04/02 16:36:12 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_42.h"
#include "builtins.h"
#include "var.h"
#include "misc.h"
#include "errors.h"

static void	add_prefix(t_string *curpath, bool *must_print_pwd, const char *dir)
{
	t_string	next;
	const char	*cdpaths;
	const char	*current;

	if (var_get("CDPATH", &cdpaths) == OK_)
	{
		current = cdpaths;
		fatal_malloc(string_init(&next));
		while ((cdpaths = get_next_path(&next, cdpaths)) != NULL)
		{
			fatal_malloc(string_cat(&next, dir));
			if (is_dir(next.str))
			{
				string_shutdown(curpath);
				*curpath = next;
				*must_print_pwd = current[0] != ':';
				return ;
			}
			current = cdpaths;
		}
		string_shutdown(&next);
	}
	fatal_malloc(string_cat(curpath, dir));
}

static int	rewind_path(t_string *curpath)
{
	if (!is_dir(curpath->str))
	{
		error_set_context("%s: %s", curpath->str, strerror(errno));
		return (ERROR_);
	}
	string_remove_back(curpath, 1);
	string_remove_back_chr(curpath, '/');
	fatal_malloc(string_cat(curpath, "/"));
	return (OK_);
}

static int	simplify_path(t_string *curpath)
{
	t_string	elem;
	t_string	build_path;
	const char	*path;
	int			ret;

	fatal_malloc(string_init(&elem));
	fatal_malloc(string_init(&build_path));
	path = curpath->str;
	ret = OK_;
	while (ret == OK_ && (path = get_next_component(&elem, path)) != NULL)
	{
		if (ft_streq(elem.str, "."))
			continue ;
		if (ft_streq(elem.str, "..") && (ret = rewind_path(&build_path)) == OK_)
			continue ;
		fatal_malloc(string_append(&build_path, &elem));
		fatal_malloc(string_ncat(&build_path, "/", 1));
	}
	string_shutdown(curpath);
	if (build_path.len > 1 && build_path.str[build_path.len - 1] == '/')
		string_remove_back(&build_path, 1);
	*curpath = build_path;
	string_shutdown(&elem);
	return (ret);
}

int			logical_resolution(t_string *curpath, const char *pwd, size_t wdlen)
{
	t_string	chdir_path;

	if (curpath->str[0] != '/')
	{
		fatal_malloc(string_insert(curpath, 0, "/", 1));
		fatal_malloc(string_insert(curpath, 0, pwd, wdlen));
	}
	if (simplify_path(curpath) == -1)
		return (ERROR_);
	fatal_malloc(string_clone(&chdir_path, curpath));
	if (!ft_strncmp(pwd, curpath->str, wdlen) && curpath->str[wdlen] == '/')
	{
		string_remove(&chdir_path, 0, ft_strlen(pwd));
		fatal_malloc(string_insert(&chdir_path, 0, ".", 1));
	}
	if (chdir(chdir_path.str) == -1)
	{
		error_set_context("%s: %s", chdir_path.str, strerror(errno));
		string_shutdown(&chdir_path);
		return (ERROR_);
	}
	var_set("OLDPWD", pwd);
	var_set("PWD", curpath->str);
	string_shutdown(&chdir_path);
	return (OK_);
}

void		get_base_path(t_string *curpath, bool *must_print_pwd,
						const char *dir)
{
	t_string	comp;

	if (dir[0] == '/')
		fatal_malloc(string_cat(curpath, dir));
	else
	{
		fatal_malloc(string_init(&comp));
		get_next_component(&comp, curpath->str);
		if (ft_streq(comp.str, ".") || ft_streq(comp.str, ".."))
			fatal_malloc(string_cat(curpath, dir));
		else
			add_prefix(curpath, must_print_pwd, dir);
		string_shutdown(&comp);
	}
}
