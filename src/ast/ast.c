#include "pool_42.h"
#include "error_42.h"
#include "ast.h"

t_ast	*ast_init(t_ast *ast)
{
	if (pool_init(&ast->pool, sizeof(t_ast_node)) == NULL)
		return (NULL);
	ast->root = NULL;
	return (ast);
}

void	ast_clear(t_ast *ast)
{
	ast->root = NULL;
	ast_nodes_clear(ast);
}

void	ast_shutdown(t_ast *ast)
{
	pool_shutdown(&ast->pool);
}
