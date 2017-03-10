#include "unistd_42.h"
#include "history.h"
#include "automaton.h"
#include "stdlib_42.h"
#include "errors.h"
#include "str_42.h"
#include "builtins.h"
#include "opt.h"

#define FLAG_REVERSE (1U << 1)
#define FLAG_NONUMBER (1U << 2)

static void		history_list(size_t first, size_t last, unsigned flags)
{
	size_t	i;
	size_t	tmp_id;
	bool	forward;

	forward = last >= first;
	i = (forward ? last - first : first - last) + 1;
	tmp_id = first;
	while (i != 0)
	{
		if (flags & FLAG_NONUMBER)
			ft_printf("\t%s\n", history_get(tmp_id)->str);
		else
			ft_printf("%d\t%s\n", tmp_id, history_get(tmp_id)->str);
		if (forward)
			tmp_id += 1;
		else
			tmp_id -= 1;
		i -= 1;
	}
}

static size_t	get_index(const char *a)
{
	size_t	id;
	size_t	history_first;
	size_t	history_last;

	history_first = history_get_first_id();
	history_last = history_get_last_id();
	if (ft_strisnum(a))
	{
		if (a[0] == '-')
		{
			id = ft_atou(a + 1);
			id = history_last - history_first <= id ?
				history_first :
				history_last - id + 1;
		}
		else
			id = FT_MIN(FT_MAX(ft_atou(a), history_first), history_last);
	}
	else
	{
		id = history_get_last_str_id(a);
		if (id == 0)
			error_set_context("not in history: %s", a);
	}
	return (id);
}

static int		builtin_history_third_and_final(int ac, const char *const *av,
												unsigned int flags)
{
	size_t			first;
	size_t			last;

	if (ac > 0)
		first = get_index(av[0]);
	else
		first = history_get_first_id();
	if (first == 0)
		return (1);
	if (ac > 1)
		last = get_index(av[1]);
	else
		last = history_get_last_id();
	if (last == 0)
		return (1);
	if (flags & FLAG_REVERSE)
		history_list(last, first, flags);
	else
		history_list(first, last, flags);
	return (0);
}

static int		builtin_history_part_ii(t_opt *o, unsigned int *flags,
									int ac, const char *const *av)
{
	int				option;

	while ((option = ft_getopt(ac, av, "nr", o)) != -1)
	{
		if (option == 'n')
			*flags |= FLAG_NONUMBER;
		else if (option == 'r')
			*flags |= FLAG_REVERSE;
		else if (option == '?')
		{
			ft_dprintf(2, "%s: %s: bad option: -%c.\n",
						BIN_NAME, av[0], o->optopt);
			return (1);
		}
	}
	return (0);
}

int				builtin_history(int ac, const char *const *av)
{
	t_opt			o;
	unsigned int	flags;

	if (opt_is_set(!OPT_INTERACTIVE))
		return ((ft_dprintf(2, "%s: %s: history functions not available",
							BIN_NAME, av[0]) & 0) | 1);
	if (history_get_last_id() == 0)
	{
		ft_dprintf(2, "%s: %s: no history (yet)\n", BIN_NAME, av[0]);
		return (1);
	}
	flags = 0x0;
	OPT_INIT(o);
	if (builtin_history_part_ii(&o, &flags, ac, av) == 1)
		return (1);
	ac -= o.optind;
	if (ac <= 2)
	{
		if (builtin_history_third_and_final(ac, av + o.optind, flags) == 0)
			return (0);
		error_print(av[0]);
		return (1);
	}
	ft_dprintf(2, "%s: usage: %s [-nr] [first [last]].\n", BIN_NAME, av[0]);
	return (1);
}
