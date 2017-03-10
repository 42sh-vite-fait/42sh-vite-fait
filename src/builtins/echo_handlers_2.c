#include "builtins.h"

/*
** \r
** Append a <carriage-return>.
*/

int	echo_handlers_carriage_return(const char *arg, t_string *buf)
{
	(void)arg;
	fatal_malloc(string_ncat(buf, "\r", 1));
	return (1);
}

/*
** \t
** Append a <tab>.
*/

int	echo_handlers_tab(const char *arg, t_string *buf)
{
	(void)arg;
	fatal_malloc(string_ncat(buf, "\t", 1));
	return (1);
}

/*
** \v
** Append a <vertical-tab>.
*/

int	echo_handlers_vertical_tab(const char *arg, t_string *buf)
{
	(void)arg;
	fatal_malloc(string_ncat(buf, "\v", 1));
	return (1);
}

/*
** \\
** Append a backslash character.
*/

int	echo_handlers_backslash(const char *arg, t_string *buf)
{
	(void)arg;
	fatal_malloc(string_ncat(buf, "\\", 1));
	return (1);
}

/*
** \0num
** Append an 8-bit value that is the zero, one,
** two, or three-digit octal number num.
*/

int	echo_handlers_num(const char *arg, t_string *buf)
{
	size_t	i;
	char	count;

	i = 1;
	count = 0;
	while (arg[i + 1] && i < 4 && arg[i + 1] >= '0' && arg[i + 1] < '8')
	{
		count *= 8;
		count += arg[i + 1] - '0';
		i++;
	}
	fatal_malloc(string_ncat(buf, &count, 1));
	return (i);
}
