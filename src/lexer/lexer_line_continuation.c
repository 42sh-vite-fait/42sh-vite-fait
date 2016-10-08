#include "lexer.h"
#include "string_42.h"
#include "misc.h"

int			remove_trailing_escaped_newline(t_string *input)
{
	if (input->len >= 2
		&& input->str[input->len - 1] == '\n'
		&& is_escaped(input->str + input->len - 1, input->str))
	{
		string_remove_back(input, 2);
		return (LINE_INCOMPLETE);
	}
	return (LINE_COMPLETE);
}
