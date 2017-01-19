#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

int	startup_redirection_init(void);
int	exec_redirection_input(int io_number, const char *word);
int	exec_redirection_output_trunc(int io_number, const char *word);
int	exec_redirection_output_append(int io_number, const char *word);
int	exec_redirection_input_duplicate(int io_number, const char *word);
int	exec_redirection_output_duplicate(int io_number, const char *word);

#endif
