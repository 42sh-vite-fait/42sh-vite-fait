#include "exec.h"
#include <assert.h>
#include "exit_status.h"

t_tree_walker	*const g_walkers[] =
{
	[E_AST_COMPLETE_COMMANDS] = &exec_node_complete_commands,
	[E_AST_COMPLETE_COMMAND] = &exec_node_complete_command,
	[E_AST_LIST] = &exec_node_list,
	[E_AST_AND_OR] = &exec_node_and_or,
	[E_AST_PIPE_SEQUENCE] = &exec_node_pipe,
	[E_AST_SUBSHELL] = &exec_node_subshell,
	[E_AST_TERM] = &exec_node_term,
	[E_AST_SIMPLE_COMMAND] = &exec_node_simple_command,
};

int exec_ast(const t_ast ast, const t_string *input)
{
	int	exit_status;

	assert(ast.root != NULL);
	exit_status = g_walkers[ast.root->type](ast.root, input);
	exit_status_set_last(exit_status);
	return (exit_status);
}
