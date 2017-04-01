/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_backup_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:01:48 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:01:52 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include "errors.h"
#include "exec.h"

static int	set_close_on_exec_flag(int fd)
{
	int	flags;

	flags = fcntl(fd, F_GETFD);
	if (flags == -1)
	{
		error_set_context("fcntl: %s", strerror(errno));
		return (ERROR_);
	}
	flags |= FD_CLOEXEC;
	if (fcntl(fd, F_SETFD, flags) == -1)
	{
		error_set_context("fcntl: %s", strerror(errno));
		return (ERROR_);
	}
	return (OK_);
}

int			exec_backup_fd(int fd, int new_fd)
{
	assert(fd >= 0);
	if (exec_dup_fd(fd, new_fd) != OK_)
		return (ERROR_);
	if (set_close_on_exec_flag(new_fd) != OK_)
		return (ERROR_);
	return (OK_);
}
