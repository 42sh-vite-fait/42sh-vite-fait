#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "ast.h"
# include "errors.h"
# include "array_42.h"

# define IS_FD_STANDARD(f) ((f) <= 2)
# define MAX_FD_POSIX_COMPLIANCE (9)

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

/*
** Tree Walker
*/
int exec_ast(const t_ast ast);
int	exec_node_complete_commands(const t_ast_node *node);
int	exec_node_complete_command(const t_ast_node *node);
int	exec_node_list(const t_ast_node *node);
int	exec_node_and_or(const t_ast_node *node);
int	exec_node_pipe(const t_ast_node *node);
int	exec_node_term(const t_ast_node *node);
int	exec_node_subshell(const t_ast_node *node);
int	exec_node_simple_command(const t_ast_node *node);

/*
** Pipe
*/
void	exec_pipe_sequence(const t_ast_node *node);
void	exec_pipe_command(const t_command command);
void	pipe_exit_on_child_error(void);
int		pipe_init(t_pipe *pype);
int		pipe_replace_stdout(int write_end);
int		pipe_replace_stdin(int read_end);

/*
** Simple Command
*/
int		exec_simple_command_binary(const t_command command);
int		exec_simple_command_builtin(const t_command command);

// Execution
void	exec_with_path(const char *paths, char * const *av, char * const *envp);
void	exec_binary(const t_command command);

/*
** Redirections
*/
int	startup_redirection_init(void);
int	exec_backup_get_standard_fd(size_t n);
int	exec_backup_standard_fd(void);
int	exec_redirection(t_array redirections);
int	exec_redirection_input(int io_number, const char *word);
int	exec_redirection_output_trunc(int io_number, const char *word);
int	exec_redirection_output_append(int io_number, const char *word);
int	exec_redirection_input_duplicate(int io_number, const char *word);
int	exec_redirection_output_duplicate(int io_number, const char *word);


/*
** Utilities
*/
pid_t	exec_fork(pid_t *pid);
int exec_process_group_create(int pid, int pgid);
int exec_close_fd(int fd);
int exec_dup_fd(int oldfd, int newfd);
int get_exit_status(int status);
int	wait_for_children(pid_t last_pid, pid_t pgid);
t_array gather_nodes(const t_ast_node *node, int type);

#endif
