#include "parser.h"

bool		check_requirements_simple_command(const t_parser *parser)
{
	if (parser_check_current_token_type(parser, E_TOKEN_WORD)
			|| check_requirements_cmd_prefix(parser))
		return (true);
	return (false);
}

/*
** simple_command : cmd_prefix cmd_word cmd_suffix
**                | cmd_prefix cmd_word
**				  | cmd_prefix
**				  | cmd_name cmd_suffix
**				  | cmd_name
*/

int			predict_simple_command(t_parser *parser, t_ast_node *self)
{
	t_array	*words;
	t_array	*redirections;
	t_array	*assignments;

	self->type = E_AST_SIMPLE_COMMAND;
	ast_node_command_init(self);
	words = &self->command.words;
	redirections = &self->command.redirections;
	assignments = &self->command.assignments;
	if (check_requirements_cmd_prefix(parser))
		if (predict_cmd_prefix(parser, redirections, assignments) != PARSER_NO_ERROR)
			return (ERR_PARSING);
	if (!parser_check_current_token_type(parser, E_TOKEN_WORD))
		return (ERR_PARSING);
	self->token = parser_get_current_token(parser);
	array_push(words, parser_get_current_token(parser));
	parser_consume_token(parser);
	if (check_requirements_cmd_suffix(parser))
		if (predict_cmd_suffix(parser, words, redirections) != PARSER_NO_ERROR)
			return (ERR_PARSING);
	return (PARSER_NO_ERROR);
}
