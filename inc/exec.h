#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include "ast.h"

/*
 *
	[ERR_OPEN] = "open failed",
	[ERR_DUP2] = "dup2 failed",
	[ERR_CLOSE] = "close failed",
	[ERR_FCNTL] = "fcntl failed",
	[ERR_BADFD] = "bad file descriptor",
	[ERR_GRLIMIT] = "getrlimit failed",
	[ERR_SRLIMIT] = "setrlimit failed",
	[ERR_FDLIMIT] = "limit of open files too low",
	*/

typedef struct s_pipe	t_pipe;
struct s_pipe
{
	int	read;
	int	write;
};

int	exec_node(t_ast_node *node);

/*
** Pipe
*/
int	pipe_replace_stdout(int write_end);
int	pipe_replace_stdin(int read_end);
int pipe_replace_stdfd(int read_end, int write_end);

#endif
