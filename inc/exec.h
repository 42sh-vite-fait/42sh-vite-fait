#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>

typedef struct s_pipe	t_pipe;
struct s_pipe
{
	int	read;
	int	write;
};

#endif
