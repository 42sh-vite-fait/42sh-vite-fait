#include "quoting.h"
#include "expansion.h"

char					*expand_quote_removal(const char *s, size_t len)
{
	t_automaton	aut;
	char		*dst;
	char		*res;

	dst = fatal_malloc(malloc(len + 1));
	res = dst;
	quoting_automaton_init(&aut);
	while (len > 0)
	{
		if (!(*s == '"' || *s == '\'' || *s == '\\') ||
			is_char_quoted(&aut, *s))
		{
			*dst = *s;
			dst += 1;
		}
		quoting_automaton_step(&aut, *s);
		len -= 1;
		s += 1;
	}
	*dst = '\0';
	automaton_shutdown(&aut);
	return (res);
}
