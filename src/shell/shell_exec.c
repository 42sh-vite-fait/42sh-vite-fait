#include "exec.h"

int shell_exec(const t_ast ast, const t_string *input)
{
	return (exec_ast(ast, input));
}
