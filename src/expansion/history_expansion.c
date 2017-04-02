/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 15:24:31 by djean             #+#    #+#             */
/*   Updated: 2017/04/02 17:02:23 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quoting.h"
#include "memory_42.h"
#include "ctype_42.h"
#include "history.h"
#include "errors.h"

static const char	g_inhibitors[] = " \t\n";

static size_t	get_number(size_t *num, const char *event)
{
	size_t	i;
	size_t	tmp;

	i = 0;
	if (event[0] == '-')
		i = 1;
	while (FT_ISDIGIT(event[i]))
		i += 1;
	if (event[0] != '-' && i > 0)
	{
		*num = ft_atou(event);
		return (i);
	}
	else if (event[0] == '-' && i > 1)
	{
		tmp = ft_atou(event + 1);
		if (tmp >= history_get_last_id())
			*num = 0;
		else
			*num = history_get_last_id() + 1 - tmp;
		return (i);
	}
	else
		return (0);
}

static size_t	get_string(size_t *num, const char *event)
{
	size_t		i;
	char		c;

	i = 0;
	while (!ft_memchr(g_inhibitors, event[i], sizeof(g_inhibitors)))
		i += 1;
	c = event[i];
	((char *)event)[i] = '\0';
	*num = history_find_start_with(event);
	((char *)event)[i] = c;
	return (i);
}

static ssize_t	expand_event(t_string *expanded, const char *event)
{
	size_t			offset;
	size_t			id;
	t_string		error;
	const t_string	*val;

	offset = 1;
	if (event[0] == '!')
		id = history_get_last_id();
	else if ((offset = get_number(&id, event)) != 0
			|| (offset = get_string(&id, event)) != 0)
		;
	if (offset == 0)
		return (0);
	val = history_get(id);
	if (val == NULL)
	{
		fatal_malloc(string_init_ndup(&error, event - 1, offset + 1));
		error_set_context("%s : event not found", error.str);
		string_shutdown(&error);
		return (-1);
	}
	fatal_malloc(string_append(expanded, val));
	return (offset);
}

static int		inside_while(const t_string *input, t_automaton *quoting,
		t_string *expanded, size_t *i)
{
	ssize_t		offset;

	if (input->str[*i] == '!'
			&& !is_char_inhibited(quoting, input->str[*i])
			&& !ft_memchr(g_inhibitors, input->str[*i + 1],
				sizeof(g_inhibitors)))
	{
		*i += 1;
		offset = expand_event(expanded, input->str + *i);
		if (offset == -1)
			return (ERROR_);
		*i += offset;
	}
	else
	{
		fatal_malloc(string_ncat(expanded, input->str + *i, 1));
		quoting_automaton_step(quoting, input->str[*i]);
		*i += 1;
	}
	return (OK_);
}

int				expand_history(t_string *input)
{
	size_t		i;
	t_string	expanded;
	t_automaton	quoting;

	quoting_automaton_init(&quoting);
	fatal_malloc(string_init(&expanded));
	i = 0;
	while (i < input->len)
	{
		if (inside_while(input, &quoting, &expanded, &i) != OK_)
		{
			automaton_shutdown(&quoting);
			string_shutdown(&expanded);
			error_print("history expansion");
			return (ERROR_);
		}
	}
	automaton_shutdown(&quoting);
	string_shutdown(input);
	*input = expanded;
	return (OK_);
}
