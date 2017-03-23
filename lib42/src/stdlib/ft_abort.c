/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:13:03 by tvallee           #+#    #+#             */
/*   Updated: 2016/12/13 15:18:56 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _POSIX_C_SOURCE 1
# include <sys/types.h>
#endif
#include <signal.h>
#include <unistd.h>
#include "str_42.h"

void	ft_abort(const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	kill(0, SIGABRT);
}
