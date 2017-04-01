#include <assert.h>
#include "lexer.h"
#include "string_42.h"
#include "misc.h"
#include "quoting.h"

int			remove_escaped_newline(t_string *input)
{
	t_automaton	quoting;
	size_t		i;

	assert(input->str != NULL);
	i = 0;
	quoting_automaton_init(&quoting);
	while (i < input->len)
	{
		if (input->str[i] == '\n' && (quoting.current_state == E_BSLASHED
			|| quoting.current_state == E_DQUOTEDBSLASHED))
		{
			quoting_automaton_step(&quoting, input->str[i]);
			string_remove(input, i - 1, 2);
			i -= 1;
			continue ;
		}
		quoting_automaton_step(&quoting, input->str[i]);
		i += 1;
	}
	automaton_shutdown(&quoting);
	if (input->len == 0 || input->str[input->len - 1] != '\n')
		return (LINE_INCOMPLETE);
	return (LINE_COMPLETE);
}
