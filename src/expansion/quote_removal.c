#include "automaton.h"
#include "string_42.h"
#include "expansion.h"

static const t_transition	g_trans_table[][1][E_SYMBOL_MAX] =
{
	[E_ERROR] = {{TRANS(E_ERROR)}},
	[E_START] =
	{{
			[E_CHAR] = TRANS(E_START),
			[E_QUOTE] = TRANS(E_QUOTED),
			[E_DQUOTE] = TRANS(E_DQUOTED),
			[E_BSLASH] = TRANS(E_BSLASHED),
		}},
	[E_QUOTED] =
	{{
			[E_CHAR] = TRANS(E_QUOTED),
			[E_QUOTE] = TRANS(E_START),
			[E_DQUOTE] = TRANS(E_QUOTED),
			[E_BSLASH] = TRANS(E_QUOTED),
		}},
	[E_DQUOTED] =
	{{
			[E_CHAR] = TRANS(E_DQUOTED),
			[E_QUOTE] = TRANS(E_DQUOTED),
			[E_DQUOTE] = TRANS(E_START),
			[E_BSLASH] = TRANS(E_DQUOTEDBSLASHED),
		}},
	[E_BSLASHED] =
	{{
			[E_CHAR] = TRANS(E_START),
			[E_QUOTE] = TRANS(E_START),
			[E_DQUOTE] = TRANS(E_START),
			[E_BSLASH] = TRANS(E_START),
		}},
	[E_DQUOTEDBSLASHED] =
	{{
			[E_CHAR] = TRANS(E_DQUOTED),
			[E_QUOTE] = TRANS(E_DQUOTED),
			[E_DQUOTE] = TRANS(E_DQUOTED),
			[E_BSLASH] = TRANS(E_DQUOTED),
		}},
};

static t_symbol			to_symbol(char c)
{
	if (c == '"')
		return (E_DQUOTE);
	if (c == '\'')
		return (E_QUOTE);
	if (c == '\\')
		return (E_BSLASH);
	return (E_CHAR);
}

inline static bool		is_next_char_litteral(char c, t_state state)
{
	if (c == '"' && (state == E_DQUOTED || state == E_START))
		return (false);
	if (c == '\'' && (state == E_START || state == E_QUOTED))
		return (false);
	if (c == '\\' && (state == E_START || state == E_DQUOTED))
		return (false);
	return (true);
}

char					*expand_quote_removal(const char *s, size_t len)
{
	t_automaton	aut;
	char		*dst;
	char		*res;

	dst = fatal_malloc(malloc(len + 1));
	res = dst;
	automaton_init(&aut, CREATE_ARRAY_3D(g_trans_table));
	while (len > 0)
	{
		if (is_next_char_litteral(*s, aut.current_state))
		{
			*dst = *s;
			dst += 1;
		}
		automaton_step(&aut, to_symbol(*s));
		len -= 1;
		s += 1;
	}
	*dst = '\0';
	return (res);
}
