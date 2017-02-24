#include <assert.h>
#include "ast.h"
#include "exec.h"
#include "builtins.h"

extern t_tree_walker	*const g_walkers[];

int		exec_node_simple_command(const t_ast_node *node)
{
	t_token	*token;
	int		ret;

	assert(node != NULL);
	token = array_get_first(&node->command.words);
	if (is_builtin(token->str, token->len))
		ret = exec_simple_command_builtin(node->command);
	else
		ret = exec_simple_command_binary(node->command);
	if (ret == -1)
		error_print("execution simple command");
	return (ret);
}
