#include "parser.h"

bool	check_requirements_simple_command(const t_parser *parser)
{
	if (parser_check_current_token_type(parser, E_TOKEN_WORD)
			|| check_requirements_cmd_prefix(parser))
		return (true);
	return (false);
}

static int	only_redirections(t_ast_node *self, t_array *redirections)
{
	static const t_token	only_redir = {

	.start = 0,
	.len = 0,
	.type = E_TOKEN_WORD
	};
	self->token = &only_redir;
	if (redirections->len == 0)
		return (ERROR_);
	return (OK_);
}

/*
** simple_command : cmd_prefix cmd_word cmd_suffix
**                | cmd_prefix cmd_word
**				  | cmd_prefix
**				  | cmd_name cmd_suffix
**				  | cmd_name
*/

int		predict_simple_command(t_parser *parser, t_ast_node *self)
{
	t_array	*words;
	t_array	*redirections;

	self->type = E_AST_SIMPLE_COMMAND;
	ast_node_command_init(self);
	words = &self->command.words;
	redirections = &self->command.redirections;
	if (check_requirements_cmd_prefix(parser))
		if (predict_cmd_prefix(parser, redirections) != OK_)
			return (ERROR_);
	if (!parser_check_current_token_type(parser, E_TOKEN_WORD))
		return (only_redirections(self, redirections));
	self->token = parser_get_current_token(parser);
	fatal_malloc(array_push(words, &self->token));
	parser_consume_token(parser);
	if (check_requirements_cmd_suffix(parser))
		if (predict_cmd_suffix(parser, words, redirections) != OK_)
			return (ERROR_);
	return (OK_);
}
