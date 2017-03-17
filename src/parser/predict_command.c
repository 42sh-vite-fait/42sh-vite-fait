#include "parser.h"

bool	check_requirements_command(const t_parser *parser)
{
	if (check_requirements_simple_command(parser)
			|| check_requirements_subshell(parser))
		return (true);
	return (false);
}

/*
** command : simple_command
**         | subshell
**         | subshell redirect_list
*/

int		predict_command(t_parser *parser, t_ast_node **from_parent)
{
	t_ast_node	*node;

	node = ast_node_create(&parser->ast);
	*from_parent = node;
	if (check_requirements_subshell(parser))
	{
		parser->subshell_depth += 1;
		if (parser->subshell_depth >= SUBSHELL_MAX_DEPTH)
			return (ERR_PARSING);
		if (predict_subshell(parser, node) != PARSER_OK_)
			return (ERR_PARSING);
		ast_node_command_init(node);
		if (check_requirements_redirect_list(parser))
			return (predict_redirect_list(parser, &node->command.redirections));
		parser->subshell_depth = 0;
	}
	else
		return (predict_simple_command(parser, node));
	return (PARSER_OK_);
}
