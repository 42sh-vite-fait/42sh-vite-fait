#include <assert.h>
#include "exec.h"
#include "array_42.h"

t_array gather_nodes(const t_ast_node *node, bool (*pred)(int node_type))
{
	t_array	stack;

	assert(node != NULL);
	assert(pred != NULL);
	fatal_malloc(array_init(&stack, sizeof(t_ast_node*)));
	while ((*pred)(node->type))
	{
		fatal_malloc(array_push(&stack, &node->right));
		node = node->left;
	}
	array_push(&stack, &node);
	return (stack);
}
