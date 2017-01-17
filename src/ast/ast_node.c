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
	return (p);
}

void		ast_node_remove(t_ast *ast, t_ast_node *node)
{
	pool_release_node(&ast->pool, node);
}

void	ast_nodes_shutdown(t_ast *ast)
{
	t_ast_node	*node;
	t_array		nodes;

	array_init(&nodes, sizeof(node));
	node = ast->root;
	while (node != NULL)
	{
		if (node->left != NULL)
			array_push(&nodes, &node->left);
		if (node->right != NULL)
			array_push(&nodes, &node->right);
		ast_node_command_shutdown(node);
		if (nodes.len != 0)
			array_pop(&nodes, &node);
		else
			node = NULL;
	}
	array_shutdown(&nodes);
}

