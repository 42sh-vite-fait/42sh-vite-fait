#include <unistd.h>
// #include <fcntl.h>
#include "typedefs_42.h"
#include "history.h"
#include "error_42.h"

// static char		*escape_command(const char *command, int fd)
// {
// 	char		*esc_cmd;
// 	size_t		command_len;
// 	size_t		nb_nl;

// 	nb_nl = 0;
// 	command_len = 0;
// 	while (command[command_len] != '\0')
// 	{
// 		if (command[command_len] == '\n')
// 			++nb_nl;
// 		++command_len;
// 	}

// 	// TODO do not create buffer each time
// 	if ((esc_cmd = malloc((command_len + nb_nl + 1) * sizeof(char))) == NULL)
// 		return (NULL);

// 	while (ft_memccpy(esc_cmd, ) != NULL)
// 	{

// 	}
// 	esc_cmd[command_len + nb_nl + 1] = '\0';
// }

// // TODO does all commands have '\n' at end ?
// int				history_save_into_file(t_history const *history, int fd)
// {
// 	// char		*buffer; // TODO use buffer for perfs
// 	const char	*command;
// 	size_t		command_len;
// 	ssize_t		ret;
// 	size_t		i;

// 	if (ftruncate(fd, 0) == -1)
// 		return (-1); // TODO errno ?

// 	// if ((buffer = malloc(WRITE_BUFF_LEN * sizeof(char))) == NULL)
// 	// {
// 	// 	ft_perror("malloc: Out of memory");
// 	// 	return (12); // TODO #define ENOMEM 12 /* Out of memory */
// 	// }

// 	i = history->last_id;
// 	while (i > history->last_id - history->cbuffer.len)
// 	{
// 		command = history_get_id(history, i);
// 		command_len = ft_strlen(command); // TODO use t_buffer (t_string*)

// 		ret = 0;
// 		// TODO add \\ in front of \n on command (buffer)
// 		while ((ret = write(fd, command + (size_t)ret, command_len - (size_t)ret)) != 0)
// 		{
// 			if (ret == -1)
// 			{
// 				// free(buffer)
// 				return (-1);
// 			}
// 		}
// 		--i;
// 	}
// 	// free(buffer);
// 	return (0);
// }

// int			history_load_from_file(t_history *history, int fd)
// {
// 	//
// 	return (0);
// }
