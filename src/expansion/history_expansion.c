#include "quoting.h"
#include "memory_42.h"
#include "ctype_42.h"
#include "history.h"
#include "errors.h"

static const char	inhibitors[] = " \t\n";

size_t	get_number(size_t *num, const char *event)
{
	size_t	i;

	i = 0;
	while(FT_ISDIGIT(event[i]))
		i += 1;
	if (i != 0)
		*num = ft_atou(event);
	return (i);
}

size_t	get_neg_number(size_t *num, const char *event)
{
	size_t	i;
	size_t	tmp;

	if (event[0] != '-')
		return (0);
	i = 1;
	while(FT_ISDIGIT(event[i]))
		i += 1;
	if (i != 0)
	{
		tmp = ft_atou(event + 1);
		if (tmp >= history_get_last_id())
			tmp = 0;
		else
			tmp -= history_get_last_id();
		*num = tmp;
	}
	return (i);
}

size_t	get_string(size_t *num, const char *event)
{
	size_t		i;
	char		c;
	t_result	r;

	i = 0;
	while (!ft_memchr(inhibitors, event[i], sizeof(inhibitors)))
		i += 1;
	c = event[i];
	((char *)event)[i] = '\0';
	if (history_find(&r, event))
		*num = r.command_id;
	else
		*num = 0;
	((char *)event)[i] = c;
	return (i);
}

ssize_t	expand_event(t_string *expanded, const char *event)
{
	size_t		offset;
	size_t		id;
	t_string	error;
	const t_string	*val;

	id = 0;
	if (event[0] == '!')
	{
		offset = 1;
		id = history_get_last_id();
	}
	else if ((offset = get_number(&id, event)) != 0)
		;
	else if ((offset = get_neg_number(&id, event)) != 0)
		;
	else if ((offset = get_string(&id, event)) != 0)
		;
	if (offset == 0)
		return (0);
	val = history_get(id);
	if (val == NULL)
	{
		string_init_ndup(&error, event, offset);
		error_set_context("%s : event not found", error.str);
		return (-1);
	}
	string_append(expanded, val);
	return (offset);
}

int		expand_history(t_string *input)
{
	size_t		prev_i;
	size_t		i;
	t_string	expanded;
	t_automaton	quoting;
	char		c;
	char		c1;
	size_t		offset;

	quoting_automaton_init(&quoting);
	string_init(&expanded);
	i = 0;
	prev_i = i;
	while (i < input->len)
	{
		c = input->str[i];
		c1 = input->str[i + 1];
		if (c == '!' && !is_char_inhibited(&quoting, c)
			&& !ft_memchr(inhibitors, c1, sizeof(inhibitors)))
		{
			string_ncat(&expanded, input->str + prev_i, i - prev_i);
			offset = expand_event(&expanded, input->str + i);
			if (offset == 0)
			{
				error_print("history expansion");
				return (ERROR_);
			}
			i += offset;
			prev_i = i;
			continue ;
		}
		quoting_automaton_step(&quoting, c);
		i += 1;
	}
	automaton_shutdown(&quoting);
	string_shutdown(input);
	*input = expanded;
	return (OK_);
}
