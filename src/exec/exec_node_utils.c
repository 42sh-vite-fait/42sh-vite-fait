#include <assert.h>
#include "array_42.h"
#include "ast.h"

t_array gather_nodes(const t_ast_node *node, int type)
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
	assert(stack.len > 0);
	return (stack);
}
