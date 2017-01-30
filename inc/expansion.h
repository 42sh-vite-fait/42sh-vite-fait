#ifndef EXPANSION_H
# define EXPANSION_H

# include <stddef.h>
# include "automaton.h"

enum e_transitions
{
	E_ERROR = ERROR_STATE,
	E_START = START_STATE,
	E_QUOTED,
	E_DQUOTED,
	E_BSLASHED,
	E_DQUOTEDBSLASHED,
};

enum e_symbols
{
	E_CHAR,
	E_QUOTE,
	E_DQUOTE,
	E_BSLASH,
	E_SYMBOL_MAX,
};

typedef enum e_transitions	t_transitions;
typedef enum e_symbols		t_symbols;

char	*expand_quote_removal(const char *s, size_t len);

#endif
