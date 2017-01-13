#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

#include "array_42.h"

#define IS_FD_STANDARD(f) ((f) >= 0 || (f) <= 2)

int	startup_redirection_init(void);
int	get_backup_standard_fd(size_t n);
int	exec_redirection(t_array redirections);
int	exec_redirection_input(int io_number, const char *word);
int	exec_redirection_output_trunc(int io_number, const char *word);
int	exec_redirection_output_append(int io_number, const char *word);
int	exec_redirection_input_duplicate(int io_number, const char *word);
int	exec_redirection_output_duplicate(int io_number, const char *word);

#endif
