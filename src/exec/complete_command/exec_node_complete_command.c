#include <assert.h>
#include "exec.h"
#include "ast.h"

extern t_tree_walker	*const g_walkers[];

int		exec_node_complete_commands(const t_ast_node *node, const t_string *input)
{
	t_array	complete_commands_nodes_stack;
	int		ret;

	assert(node != NULL);
	complete_commands_nodes_stack = gather_childrens_nodes(node, E_AST_COMPLETE_COMMANDS);
	array_pop(&complete_commands_nodes_stack, &node);
	ret = g_walkers[node->type](node, input);
	while (complete_commands_nodes_stack.len > 0)
	{
		array_pop(&complete_commands_nodes_stack, &node);
		ret = g_walkers[node->type](node, input);
	}
	array_shutdown(&complete_commands_nodes_stack);
	return (ret);
}

int		exec_node_complete_command(const t_ast_node *node, const t_string *input)
{
	t_array	complete_command_nodes_stack;
	int		ret;

	assert(node != NULL);
	complete_command_nodes_stack = gather_childrens_nodes(node, E_AST_COMPLETE_COMMAND);
	array_pop(&complete_command_nodes_stack, &node);
	ret = g_walkers[node->type](node, input);
	while (complete_command_nodes_stack.len > 0)
	{
		array_pop(&complete_command_nodes_stack, &node);
		ret = g_walkers[node->type](node, input);
	}
	array_shutdown(&complete_command_nodes_stack);
	return (ret);
}
