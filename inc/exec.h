#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "ast.h"
# include "errors.h"
# include "array_42.h"

# define IS_FD_STANDARD(f)			((f) <= 2)
# define BACKUP_FD_OFFSET			(10)
# define BACKUP_TTY_FD				(3)
# define FD_CLOSED					(-1)
# define MAX_FD_POSIX_COMPLIANCE	(9)
# define OPEN_DEFAULT_MODE			(0644)

typedef int (t_tree_walker)(const t_ast_node *, const t_string *);
typedef struct s_pipe	t_pipe;
struct s_pipe
{
	int	read;
	int	write;
};

/*
** Tree Walker
*/
int 	exec_ast(const t_ast ast, const t_string *input);
int		exec_node_complete_commands(const t_ast_node *node, const t_string *input);
int		exec_node_complete_command(const t_ast_node *node, const t_string *input);
int		exec_node_list(const t_ast_node *node, const t_string *input);
int		exec_node_and_or(const t_ast_node *node, const t_string *input);
int		exec_node_pipe(const t_ast_node *node, const t_string *input);
int		exec_node_term(const t_ast_node *node, const t_string *input);
int		exec_node_subshell(const t_ast_node *node, const t_string *input);
int		exec_node_simple_command(const t_ast_node *node, const t_string *input);

/*
** Pipe
*/
void	exec_pipe_sequence(const t_ast_node *node, const t_string *input);
void	exec_pipe_command(const t_ast_node *node, const t_string *input);
void	pipe_kill_pipe_sequence(void);
int		pipe_init(t_pipe *pype);
int		pipe_replace_stdout(int write_end);
int		pipe_replace_stdin(int read_end);

/*
** Simple Command
*/
int		exec_simple_command_binary(const t_command command, const t_string *input);
int		exec_simple_command_builtin(const t_command command, const t_string *input);

// Execution
void	exec_with_path(const char *paths, char * const *av, char * const *envp);
void	exec_binary(const t_command command, const t_string *input);

/*
** Backup fd
*/
int		init_exec_module(void);
int		exec_get_backup_fd(unsigned n);
void	exec_set_backup_fd(unsigned index, int new_fd);
int		exec_backup_fd(int fd, int new_fd);

/*
** Redirections
*/
bool	is_fd_open(int fd);
int		exec_redirection(const t_array redirections, const t_string *input);
int		undo_redirection(const t_array redirections);
int		exec_redirection_input(int io_number, const char *word);
int		exec_redirection_output_trunc(int io_number, const char *word);
int		exec_redirection_output_append(int io_number, const char *word);
int		exec_redirection_input_duplicate(int io_number, const char *word);
int		exec_redirection_output_duplicate(int io_number, const char *word);


/*
** Process utilities
*/
pid_t	exec_fork(pid_t *pid);
int		wait_child_process_group(pid_t last_pid, pid_t pgid);

/*
** Process Group Utilities
*/
void 	exec_child_set_context(void);
int 	exec_parent_wait_child_process_group(pid_t child_pgid);

/*
** IO utilities
*/
int 	exec_close_fd(int fd);
int 	exec_dup_fd(int oldfd, int newfd);

/*
** Node utilities
*/
t_array gather_childrens_nodes(const t_ast_node *node, int type);
t_array gather_nodes_token_type(const t_ast_node *node, int type);

#endif
