#include "builtins.h"

/*
** \a
** Append an <alert>.
*/

int	echo_handlers_alert(const char *arg, t_string *buf)
{
	(void)arg;
	fatal_malloc(string_ncat(buf, "\a", 1));
	return (1);
}

/*
** \b
** Append a <backspace>.
*/

int	echo_handlers_backspace(const char *arg, t_string *buf)
{
	(void)arg;
	fatal_malloc(string_ncat(buf, "\b", 1));
	return (1);
}

/*
** \f
** Append a <form-feed>.
*/

int	echo_handlers_form_feed(const char *arg, t_string *buf)
{
	(void)arg;
	fatal_malloc(string_ncat(buf, "\f", 1));
	return (1);
}

/*
** \n
** Append a <newline>.
*/

int	echo_handlers_newline(const char *arg, t_string *buf)
{
	(void)arg;
	fatal_malloc(string_ncat(buf, "\n", 1));
	return (1);
}
