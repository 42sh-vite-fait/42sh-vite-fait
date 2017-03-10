#include "builtins.h"

static bool		parse_arg(t_string *buf, const char *arg)
{
	size_t		i;
	static int	(*char_to_func[256])(const char*, t_string *) = {
		['a'] = echo_handlers_alert,
		['b'] = echo_handlers_backspace,
		['f'] = echo_handlers_form_feed,
		['n'] = echo_handlers_newline,
		['r'] = echo_handlers_carriage_return,
		['t'] = echo_handlers_tab,
		['v'] = echo_handlers_vertical_tab,
		['\\'] = echo_handlers_backslash,
		['0'] = echo_handlers_num
	};

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '\\' && arg[i + 1] != 0 && char_to_func[(int)arg[i + 1]])
			i += char_to_func[(int)arg[i + 1]](arg + i, buf);
		else if (arg[i] == '\\' && arg[i + 1] == 'c')
			return (false);
		else
			fatal_malloc(string_ncat(buf, arg + i, 1));
		i++;
	}
	return (true);
}

static bool		fill_buffer(t_string *buf, const char *arg, bool is_last_arg)
{
	if (!parse_arg(buf, arg))
		return (false);
	if (!is_last_arg)
		fatal_malloc(string_ncat(buf, " ", 1));
	return (true);
}

int				builtin_echo(int argc, const char *const *argv)
{
	int			i;
	bool		nl;
	t_string	buf;

	argc--;
	argv++;
	nl = true;
	i = 0;
	fatal_malloc(string_init(&buf));
	while (i < argc)
	{
		if (!fill_buffer(&buf, argv[i], (i == argc - 1)))
		{
			nl = false;
			break ;
		}
		i++;
	}
	ft_printf(nl ? "%s\n" : "%s", buf.str);
	string_shutdown(&buf);
	return (0);
}
