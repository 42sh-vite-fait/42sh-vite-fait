#include "exec.h"

t_tree_walker	*const g_walkers[] =
{
	[E_AST_LIST] = &exec_node_list,
	[E_AST_AND_OR] = &exec_node_andor,
	[E_AST_PIPE_SEQUENCE] = &exec_node_pipe,
	[E_AST_SIMPLE_COMMAND] = &exec_node_simple_command,
	[E_AST_SUBSHELL] = &exec_node_subshell,
};
