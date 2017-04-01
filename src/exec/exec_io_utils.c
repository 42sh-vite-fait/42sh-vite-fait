/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_io_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:01:48 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:05:25 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include "errors.h"
#include "exec.h"

int	exec_close_fd(int fd)
{
	if (close(fd) == -1)
	{
		error_set_context("close: %s", strerror(errno));
		return (ERROR_);
	}
	return (OK_);
}

/*
** 'origin' ---> a ; 'dup' ---> b
** dup2(origin, dup)
** 'origin' ---> a ; 'dup' ---> a
*/

int	exec_dup_fd(int origin, int dup)
{
	if (dup2(origin, dup) == -1)
	{
		error_set_context("dup2: %s", strerror(errno));
		return (ERROR_);
	}
	return (OK_);
}
