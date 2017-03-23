/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 16:35:17 by djean             #+#    #+#             */
/*   Updated: 2016/10/15 14:39:26 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_42.h"

extern int		g_errno;
int				g_errno;
static char		*g_project_name;
static char		**g_errlist;
static size_t	g_nerr;

void	register_errlist(char *name, char **list, size_t max)
{
	g_errno = 0;
	g_project_name = (name == NULL) ? "error" : name;
	g_errlist = list;
	g_nerr = max;
}

char	*ft_strerror(int errnum)
{
	if (errnum < 0 || (size_t)errnum >= g_nerr)
		return (UNKNOWN_ERROR);
	return (g_errlist[errnum]);
}

void	ft_perror(const char *msg)
{
	ft_perrorn(msg, g_errno);
}

void	ft_perrorn(const char *msg, int errnum)
{
	t_string	buf;
	char		*errmsg;

	string_init(&buf);
	string_cat(&buf, g_project_name);
	string_ncat(&buf, ": ", 2);
	if (msg != NULL && msg[0] != '\0')
	{
		string_cat(&buf, msg);
		string_ncat(&buf, ": ", 2);
	}
	errmsg = ft_strerror(errnum);
	string_cat(&buf, errmsg);
	write(STDERR_FILENO, buf.str, buf.len);
	free(buf.str);
}
