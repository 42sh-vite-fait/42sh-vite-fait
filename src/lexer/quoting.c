#include "quoting.h"
#include "automaton.h"
#include "string_42.h"

static const t_transition	g_trans_table[][1][E_SYMBOL_MAX] =
{
	[E_ERROR] = {{TRANS(E_ERROR)}},
	[E_UNQUOTED] =
	{{
			[E_CHAR] = TRANS(E_UNQUOTED),
			[E_QUOTE] = TRANS(E_QUOTED),
			[E_DQUOTE] = TRANS(E_DQUOTED),
			[E_BSLASH] = TRANS(E_BSLASHED),
		}},
	[E_QUOTED] =
	{{
			[E_CHAR] = TRANS(E_QUOTED),
			[E_QUOTE] = TRANS(E_UNQUOTED),
			[E_DQUOTE] = TRANS(E_QUOTED),
			[E_BSLASH] = TRANS(E_QUOTED),
		}},
	[E_DQUOTED] =
	{{
			[E_CHAR] = TRANS(E_DQUOTED),
			[E_QUOTE] = TRANS(E_DQUOTED),
			[E_DQUOTE] = TRANS(E_UNQUOTED),
			[E_BSLASH] = TRANS(E_DQUOTEDBSLASHED),
		}},
	[E_BSLASHED] =
	{{
			[E_CHAR] = TRANS(E_UNQUOTED),
			[E_QUOTE] = TRANS(E_UNQUOTED),
			[E_DQUOTE] = TRANS(E_UNQUOTED),
			[E_BSLASH] = TRANS(E_UNQUOTED),
		}},
	[E_DQUOTEDBSLASHED] =
	{{
			[E_CHAR] = TRANS(E_DQUOTED),
			[E_QUOTE] = TRANS(E_DQUOTED),
			[E_DQUOTE] = TRANS(E_DQUOTED),
			[E_BSLASH] = TRANS(E_DQUOTED),
		}},
};

static t_symbol	to_symbol(char c)
{
	if (c == '"')
		return (E_DQUOTE);
	if (c == '\'')
		return (E_QUOTE);
	if (c == '\\')
		return (E_BSLASH);
	return (E_CHAR);
}

bool			is_char_quoted(t_automaton *a, char c)
{
	t_state	state;

	state = a->current_state;
	if (c == '"')
	{
		if (state == E_DQUOTED || state == E_UNQUOTED)
			return (false);
	}
	else if (c == '\'')
	{
		if (state == E_UNQUOTED || state == E_QUOTED)
			return (false);
	}
	else if (c == '\\')
	{
		if (state == E_UNQUOTED || state == E_DQUOTED)
			return (false);
	}
	else if (state == E_UNQUOTED)
		return (false);
	return (true);
}

bool			is_char_inhibited(t_automaton *a, char c)
{
	t_state	state;

	state = a->current_state;
	if (c == '"')
	{
		if (state == E_DQUOTED || state == E_UNQUOTED)
			return (false);
	}
	else if (c == '\'')
	{
		if (state == E_UNQUOTED || state == E_QUOTED)
			return (false);
	}
	else if (c == '\\')
	{
		if (state == E_UNQUOTED || state == E_DQUOTED)
			return (false);
	}
	else if (state == E_UNQUOTED || state == E_DQUOTED)
		return (false);
	return (true);
}

t_automaton		*quoting_automaton_init(t_automaton *a)
{
	return (automaton_init(a, CREATE_ARRAY_3D(g_trans_table)));
}

void			quoting_automaton_step(t_automaton *a, char c)
{
	automaton_step(a, to_symbol(c));
}
