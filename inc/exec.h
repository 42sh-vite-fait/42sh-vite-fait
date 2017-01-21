#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>

typedef struct s_pipe	t_pipe;
struct s_pipe
{
	int	read;
	int	write;
};

/*
** Pipe
*/
int	pipe_replace_stdout(int write_end);
int	pipe_replace_stdin(int read_end);
int pipe_replace_stdfd(int read_end, int write_end);

#endif
