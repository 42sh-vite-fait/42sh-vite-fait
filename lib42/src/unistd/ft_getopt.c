#include <stdbool.h>
#include "unistd_42.h"
#include "str_42.h"
#include "ft_printf.h"

#define ERR_OPT_NO_FOUND	(-1)

static bool			should_we_stop_the_parsing(const char *arg)
{
	if (arg == NULL
			|| arg[0] != '-'
			|| ft_streq(arg, "-")
			|| ft_streq(arg, "--"))
	{
		return (true);
	}
	return (false);
}

static const char	*parse_opt_with_arg(const char *const *av, t_opt *opt)
{
	const char	*arg;

	if (av[opt->current_arg][opt->current_opt + 1] != '\0')
		return (NULL);
	arg = av[opt->current_arg + 1];
	if (arg == NULL || (arg[0] == '-' && arg[1] != '\0'))
		return (NULL);
	opt->current_arg += 2;
	opt->current_opt = 1;
	return (arg);
}

static int			parse_opt(const char *const *av, const char *optstr,
		t_opt *opt)
{
	int	opt_char;

	opt_char = ERR_OPT_NO_FOUND;
	if (optstr[0] == av[opt->current_arg][opt->current_opt])
	{
		opt_char = av[opt->current_arg][opt->current_opt];
		if (optstr[1] == ':')
		{
			opt->arg = parse_opt_with_arg(av, opt);
			if (opt->arg == NULL)
				opt_char = ':';
		}
		else if (av[opt->current_arg][opt->current_opt + 1] == '\0')
		{
			opt->current_arg += 1;
			opt->current_opt = 1;
		}
		else
			opt->current_opt += 1;
	}
	return (opt_char);
}

static int			parse_arg(const char *const *av, const char *optstr,
		t_opt *opt)
{
	int	opt_char;

	while (optstr[0])
	{
		if (optstr[0] != ':')
		{
			if ((opt_char = parse_opt(av, optstr, opt)) != ERR_OPT_NO_FOUND)
				return (opt_char);
		}
		optstr += 1;
	}
	opt->unknown_opt = av[opt->current_arg][opt->current_opt];
	if (av[opt->current_arg][opt->current_opt + 1] == '\0')
	{
		opt->current_arg += 1;
		opt->current_opt = 1;
	}
	else
		opt->current_opt += 1;
	return ('?');
}

int					ft_getopt(const char *const *av, const char *optstr,
		t_opt *opt)
{
	int	ret;

	if (should_we_stop_the_parsing(av[opt->current_arg]))
	{
		opt->end = opt->current_arg;
		if (av[opt->end] != NULL && ft_streq(av[opt->end], "--"))
			opt->end += 1;
		return (-1);
	}
	ret = parse_arg(av, optstr, opt);
	if (opt->print_errmsg && (ret == '?' || ret == ':'))
	{
		if (opt->unknown_opt != -1)
			ft_dprintf(2, GETOPT_INVALID_ERR_FORMAT, av[0], opt->unknown_opt);
		else
			ft_dprintf(2, GETOPT_MULT_ERR_FORMAT, av[0],
					av[opt->current_arg][opt->current_opt]);
	}
	return (ret);
}
