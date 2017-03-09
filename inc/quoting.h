# include "automaton.h"
# define DQUOTE_BACKSLASH_SPECIAL "\"\\\n"

enum e_transitions
{
	E_ERROR = ERROR_STATE,
	E_UNQUOTED = START_STATE,
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

void			quoting_automaton_step(t_automaton *a, char c);
t_automaton		*quoting_automaton_init(t_automaton *a);
bool			is_char_quoted(t_automaton *a, char c, char next);
bool			is_char_inhibited(t_automaton *a, char c);
