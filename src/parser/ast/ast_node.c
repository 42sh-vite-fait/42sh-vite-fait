#include "ast.h"
#include "pool_42.h"

t_ast_node	*ast_node_create(t_ast *ast)
{
	t_ast_node	*p;

	fatal_malloc(p = pool_obtain_node(&ast->pool));
	p->left = NULL;
	p->right = NULL;
	p->type = E_AST_NONE;
	p->token = NULL;
	ft_memset(&p->command, 0, sizeof(t_command));
	return (p);
}

void		ast_node_remove(t_ast *ast, t_ast_node *node)
{
	pool_release_node(&ast->pool, node);
}

void		ast_nodes_clear(t_ast *ast)
{
	t_ast_node	*node;
	t_array		nodes;

	fatal_malloc(array_init(&nodes, sizeof(node)));
	node = ast->root;
	while (node != NULL)
	{
		if (node->left != NULL)
			fatal_malloc(array_push(&nodes, &node->left));
		if (node->right != NULL)
			fatal_malloc(array_push(&nodes, &node->right));
		ast_node_command_shutdown(node);
		ast_node_remove(ast, node); // TODO: segv ?
		if (nodes.len != 0)
			array_pop(&nodes, &node);
		else
			node = NULL;
	}
	array_shutdown(&nodes);
}
