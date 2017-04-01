/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:36:32 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:36:33 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "parser.h"
#include "ast.h"
#include "memory_42.h"
#include "array_42.h"
#include "pool_42.h"

t_parser	*parser_init(t_parser *parser)
{
	assert(parser != NULL);
	if (pool_init(&parser->ast.pool, sizeof(t_ast_node)) == NULL)
		return (NULL);
	parser->ast.root = NULL;
	fatal_malloc(array_init(&parser->heredocs, sizeof(struct s_redirection*)));
	return (parser);
}

void		parser_init_with_tokens(const t_string *input,
		t_parser *parser, const t_array *tokens)
{
	assert(!ARRAY_IS_EMPTY(tokens));
	assert(parser != NULL);
	assert(input != NULL);
	parser->tokens = tokens;
	parser->current_token = array_get_first(tokens);
	parser->index = 0;
	parser->subshell_depth = 0;
	parser->input = input;
}

void		parser_clear(t_parser *parser)
{
	ast_nodes_clear(&parser->ast);
	parser->ast.root = NULL;
	array_clear(&parser->heredocs);
}

void		parser_shutdown(t_parser *parser)
{
	pool_shutdown(&parser->ast.pool);
	array_shutdown(&parser->heredocs);
}
