#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include "ast.h"
# include "errors.h"

enum e_exec_errors
{
	EXEC_NO_ERROR = NO_ERROR,
	ERR_EXEC,
};

typedef int (t_tree_walker)(const t_ast_node *);
typedef struct s_pipe	t_pipe;
struct s_pipe
{
	int	read;
	int	write;
};

// Tree Walker
int	exec_node_list(const t_ast_node *node);
int	exec_node_and_or(const t_ast_node *node);
int	exec_node_pipe(const t_ast_node *node);
int	exec_node_subshell(const t_ast_node *node);
int	exec_node_simple_command(const t_ast_node *node);

// Execution
t_array	convert_to_str(t_array tokens);
int		exec_builtin(const t_command command);
int		exec_binary(const t_command command);

/*
** Pipe
*/
int		exec_node_pipe(const t_ast_node *node);
void	exec_pipe_sequence(const t_ast_node *node);
void	exec_pipe_command(const t_command command);
void	pipe_exit_on_child_error(void);
int		pipe_init(t_pipe *pype);
int		pipe_replace_stdout(int write_end);
int		pipe_replace_stdin(int read_end);

/*
** And_or
*/
int	exec_node_and_or(const t_ast_node *node);

/*
** Utilities
*/
pid_t	exec_fork(pid_t *pid);
int exec_process_group_create(int pid, int pgid);
int exec_close_fd(int fd);
int get_exit_status(int status);
int	wait_for_children(pid_t last_pid, pid_t pgid);

#endif
