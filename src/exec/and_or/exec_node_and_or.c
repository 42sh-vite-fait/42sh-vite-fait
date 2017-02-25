#include <assert.h>
#include "exec.h"

extern t_tree_walker	*const g_walkers[];

static bool	should_we_execute_next_child(int token_type, int prev_ret)
{
	if (token_type == E_TOKEN_AND_IF && prev_ret == 0)
		return (true);
	else if (token_type == E_TOKEN_OR_IF && prev_ret != 0)
		return (true);
	return (false);
}

int			exec_node_and_or(const t_ast_node *node)
{
	t_array		andor_children_stack;
	t_array		andor_token_type_stack;
	t_ast_node	*child;
	int			token_type;
	int			exit_status;

	assert(node != NULL);
	andor_children_stack = gather_childrens_nodes(node, E_AST_AND_OR);
	andor_token_type_stack = gather_nodes_token_type(node, E_AST_AND_OR);
	array_pop(&andor_children_stack, &child);
	exit_status = g_walkers[child->type](child);
	while (andor_token_type_stack.len > 0)
	{
		array_pop(&andor_token_type_stack, &token_type);
		array_pop(&andor_children_stack, &child);
		if (should_we_execute_next_child(token_type, exit_status))
			exit_status = g_walkers[child->type](child);
	}
	return (exit_status);
}
