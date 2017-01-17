#include "parser.h"

static t_parser		parser;
static t_array		array;
/* static t_ast_node	node; */

static void	setup(int *tokens_array, size_t count)
{
	array_init(&array, sizeof(t_token));
	for (size_t i = 0; i < count; ++i)
	{
		t_token *token = array_get_available(&array);
		token->type = tokens_array[i];
		token->len = 0;
		token->start = 0;
	}
	parser.index = 0;
	parser.tokens = &array;
	parser.current_token = array_get_first(parser.tokens);
}

static void teardown(void)
{
	array_shutdown(&array);
	memset(&parser, 0, sizeof(t_parser));
	/* memset(&node, 0, sizeof(t_ast_node)); */
}

#define setup_tokens(a)	(setup(a, ARR_SIZ_MAX(a)))
#define test_current_token(TOKEN)									\
	do {															\
		t_token *token = array_get_at(parser.tokens, parser.index);	\
		cr_assert_eq(token->type, TOKEN);							\
	} while (0)	
