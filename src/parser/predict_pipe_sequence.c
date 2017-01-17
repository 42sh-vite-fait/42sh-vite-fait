#include "parser.h"

bool	check_requirements_pipe_sequence(const t_parser *parser)
{
	if (check_requirements_command(parser))
		return (true);
	return (false);
}

static int	parse_right_pipe_sequence(t_parser *parser, t_ast_node *node)
{
	node->type = E_AST_PIPE_SEQUENCE;
	node->token = parser_get_current_token(parser);
	parser_consume_token(parser);
	if (predict_linebreak(parser) != NO_ERROR)
		return (ERR_PARSING);
	if (predict_command(parser, &node->right) != NO_ERROR)
		return (ERR_PARSING);
	return (NO_ERROR);
}

/*
** pipe_sequence :                             command
**               | pipe_sequence '|' linebreak command
*/

int		predict_pipe_sequence(t_parser *parser, t_ast_node **from_parent)
{
	t_ast_node	*node;

	node = ast_node_create(&parser->ast);

	*from_parent = node;

	if (predict_command(parser, &node->left) != NO_ERROR)
		return (ERR_PARSING);

	if (parser_check_current_token_type(parser, E_TOKEN_PIPE))
	{
		if (parse_right_pipe_sequence(parser, node) != NO_ERROR)
			return (ERR_PARSING);

		while (parser_check_current_token_type(parser, E_TOKEN_PIPE))
		{
			node = ast_node_create(&parser->ast);

			node->left = *from_parent;
			*from_parent = node;

			if (parse_right_pipe_sequence(parser, node) != NO_ERROR)
				return (ERR_PARSING);
		}
	}
	return (NO_ERROR);
}

/*
** Comment ça marche ?
**
** - creation d'un node pipe
** - le node courant devient le fils droit du père
** - parsing d'une simple_command comme fils-gauche
** - parsing du pipe si présent et parsing d'une simple_command en fils-droit
** - si un pipe est encore présent on doit shifter le node courant,
**		celui-ci devient le fils-gauche d'un nouveau node et le nouveau node
**		devient le fils de 'from_parent'
** - in while: l'ancien fils devient le fils-gauche du nouveau node,
**				le pointer fils-droit du père devient le nouveau node
*/
