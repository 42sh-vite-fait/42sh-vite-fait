#include "history_expansion.h"

static size_t		parse_history_substitution(t_exp *out_listexp,
						t_string command)
{
	size_t		expnum;
	size_t		i;
	t_automaton	a;

	quoting_automaton_init(&a);
	expnum = 0;
	i = 0;
	while (i < command.len && expnum < MAX_EXP)
	{
		if (command.str[i] == '!' && !is_char_inhibited(&a, command.str[i]))
		{
			quoting_automaton_step(&a, command.str[i]);
			i += identify_expansion(&out_listexp[expnum++], command, i);
		}
		else
		{
			quoting_automaton_step(&a, command.str[i]);
			i++;
		}
	}
	automaton_shutdown(&a);
	return (expnum);
}

static int			apply_substitution(t_string *command, t_exp *listexp,
						size_t expnum)
{
	t_string	list[MAX_EXP];
	int			i;
	int			dephasage;

	i = 0;
	dephasage = 0;
	while (i < (int)expnum)
	{
		string_init(&list[i]);
		if (get_substitution(listexp[i], &list[i]) < 0 && listexp[i].size > 1)
		{
			print_error(listexp[i], *command);
			free_data(listexp, list, expnum, i);
			return (-1);
		}
		i++;
	}
	i = 0;
	while (i < (int)expnum)
	{
		if (listexp[i].size > 1)
			dephasage = substitute(command, listexp[i], list[i], dephasage);
		i++;
	}
	free_data(listexp, list, i, i);
	return (0);
}

int					history_substitutions(t_string *command)
{
	t_exp		listexp[MAX_EXP];
	size_t		expnum;

	expnum = parse_history_substitution(listexp, *command);
	return (apply_substitution(command, listexp, expnum));
}
