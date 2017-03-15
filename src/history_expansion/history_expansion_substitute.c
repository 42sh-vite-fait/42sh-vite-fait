#include "history_expansion.h"

static int		get_back_num_history(size_t n, t_string *s)
{
	size_t		last_id;
	t_string	*tmp;

	n -= 1;
	last_id = history_get_last_id();
	if (n >= last_id)
		return (-1);
	tmp = (t_string*)history_get(last_id - n);
	if (tmp == NULL)
		return (-1);
	fatal_malloc(string_insert(s, 0, tmp->str, tmp->len));
	return (0);
}

static int		get_num_history(size_t n, t_string *s)
{
	size_t		last_id;
	t_string	*tmp;

	last_id = history_get_last_id();
	if (n > last_id || n == 0)
		return (-1);
	tmp = (t_string*)history_get(n);
	if (tmp == NULL)
		return (-1);
	fatal_malloc(string_insert(s, 0, tmp->str, tmp->len));
	return (0);
}

static int		get_string_history(t_string pat, t_string *s)
{
	t_result	result;
	t_string	*tmp;

	if (!(history_find(&result, pat.str)))
		return (-1);
	tmp = (t_string*)history_get(result.command_id);
	if (tmp == NULL)
		return (-1);
	fatal_malloc(string_insert(s, 0, tmp->str, tmp->len));
	return (0);
}

int				get_substitution(t_exp exp, t_string *b)
{
	if (exp.type == E_TYPE_NUM)
		return (get_num_history(exp.n_back, b));
	if (exp.type == E_TYPE_BACK_NUM)
		return (get_back_num_history(exp.n_back, b));
	if (exp.type == E_TYPE_STRING)
		return (get_string_history(exp.string, b));
	return (-1);
}

int				substitute(t_string *command, t_exp exp,
					t_string string, int dephasage)
{
	string_remove(command, exp.offset + dephasage, exp.size);
	fatal_malloc(string_insert(command, exp.offset + dephasage, string.str, string.len));
	dephasage += (int)string.len - (int)exp.size;
	return (dephasage);
}
