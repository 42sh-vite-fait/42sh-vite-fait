#include "pool_42.h"
#include "error_42.h"
#include "ast.h"

t_ast		*ast_init(t_ast *ast)
{
	fatal_malloc(pool_init(&ast->pool, sizeof(t_ast_node)));
	ast->root = NULL;
	return (ast);
}

void		ast_shutdown(t_ast *ast)
{
	ast_nodes_shutdown(ast);
	pool_shutdown(&ast->pool);
	ft_memset(ast, 0, sizeof(t_ast));
}
