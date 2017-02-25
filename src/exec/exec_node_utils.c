#include <assert.h>
#include "array_42.h"
#include "ast.h"

t_array gather_childrens_nodes(const t_ast_node *node, int type)
{
	t_array stack;

	assert(node != NULL);
	fatal_malloc(array_init(&stack, sizeof(t_ast_node*)));
	while (node->type == type)
	{
		fatal_malloc(array_push(&stack, &node->right));
		node = node->left;
	}
	fatal_malloc(array_push(&stack, &node));
	assert(stack.len >= 2);
	return (stack);
}

t_array gather_nodes_token_type(const t_ast_node *node, int type)
{
	t_array stack;

	assert(node != NULL);
	fatal_malloc(array_init(&stack, sizeof(int)));
	while (node->type == type)
	{
		fatal_malloc(array_push(&stack, &node->token->type));
		node = node->left;
	}
	assert(stack.len >= 1);
	return (stack);
}
