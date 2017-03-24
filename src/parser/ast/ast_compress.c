#include "ast.h"

static void	ast_compress_remove_current_node(t_ast *ast, t_ast_node **node)
{
	t_ast_node	*removed;

	removed = *node;
	*node = (*node)->left;
	ast_node_remove(ast, removed);
}

/*
** Règle de la compression:
** Si c'est un subshell
**	- on passe directement au fils gauche
**	- pas de compression
** Si c'est une simple_command
**	- On pop un node de la stack si il y en a un
**	- Si la stack est vide, on a terminé la compression
** Si c'est ni un subshell ni une simple_command
**	- Si le fils droit est NULL, le node est compressé
**	- Sinon, le fils droit est push sur la stack
**	et on avance dans le fils gauche
*/

static void	ast_compress_node(t_ast *ast, t_ast_node **node, t_array *stack)
{
	while (*node != NULL)
	{
		if ((*node)->type == E_AST_SUBSHELL)
			node = &(*node)->left;
		else if ((*node)->type == E_AST_SIMPLE_COMMAND)
		{
			if (stack->len > 0)
				array_pop(stack, &node);
			else
				return ;
		}
		else
		{
			if ((*node)->right == NULL)
				ast_compress_remove_current_node(ast, node);
			else
			{
				if ((*node)->right->type != E_AST_SIMPLE_COMMAND)
					fatal_malloc(array_push(stack, &(void*){&(*node)->right}));
				node = &(*node)->left;
			}
		}
	}
}

void		ast_compress(t_ast *ast)
{
	t_array	stack;

	fatal_malloc(array_init(&stack, sizeof(t_ast_node*)));
	ast_compress_node(ast, &ast->root, &stack);
	array_shutdown(&stack);
}
