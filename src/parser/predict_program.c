#include "parser.h"

/*
** program : linebreak complete_commands linebreak
**         | linebreak
*/

int	predict_program(t_parser *parser, t_ast_node **root)
{
	if (predict_linebreak(parser) != OK_)
		return (ERROR_);
	if (check_requirements_complete_commands(parser))
	{
		if (predict_complete_commands(parser, root) != OK_)
			return (ERROR_);
		if (predict_linebreak(parser) != OK_)
			return (ERROR_);
	}
	return (OK_);
}
