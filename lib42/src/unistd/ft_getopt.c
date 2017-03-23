#include <stdbool.h>
#include "unistd_42.h"
#include "str_42.h"
#include "ft_printf.h"

static void	opt_print_errmsg(const char *const *av, const t_opt *opt)
{
	if (opt->unknown_opt != -1)
		ft_dprintf(2, GETOPT_INVALID_ERR_FORMAT, av[0], opt->unknown_opt);
	else
		ft_dprintf(2, GETOPT_MULT_ERR_FORMAT, av[0], av[opt->current - 1][1]);
}

static int	parse_opts(const char *const *av, const char *optstr, t_opt *opt)
{
	while (*optstr)
	{
		if (*optstr != ':' && *optstr == av[opt->current][1])
		{
			opt->current += 1;
			if (optstr[1] == ':')
			{
				opt->arg = av[opt->current];
				if (opt->arg == NULL || ft_strcmp(opt->arg, "--") == 0)
					return (':');
				opt->current += 1;
				return (av[opt->current - 2][1]);
			}
			else
				return (av[opt->current - 1][1]);
		}
		optstr += 1;
	}
	opt->current += 1;
	opt->unknown_opt = av[opt->current - 1][1];
	return ('?');
}

static bool	should_we_stop_the_parsing(const char *const *av, t_opt *opt)
{
	if (av[opt->current] == NULL)
	{
		opt->end = opt->current;
		return (true);
	}
	else if (ft_strcmp(av[opt->current], "--") == 0)
	{
		opt->current += 1;
		opt->end = opt->current;
		return (true);
	}
	else if (av[opt->current][0] != '-')
	{
		opt->end = opt->current;
		return (true);
	}
	return (false);
}

int			ft_getopt(const char *const *av, const char *optstr, t_opt *opt)
{
	int	ret;

	opt->arg = NULL;
	opt->unknown_opt = -1;
	if (should_we_stop_the_parsing(av, opt))
		return (-1);
	ret = parse_opts(av, optstr, opt);
	if (opt->print_errmsg && (ret == '?' || ret == ':'))
		opt_print_errmsg(av, opt);
	return (ret);
}
