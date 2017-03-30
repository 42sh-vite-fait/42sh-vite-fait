/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 17:00:15 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 17:27:36 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "string_42.h"
# include "array_42.h"
# include "parser.h"

# define BIN_NAME "42sh"
# define SHELL_PS1 "42sh> "
# define SHELL_PS2 "> "

int		shell_loop(void);
int		shell_input(t_string *input, const char *prompt);
void	shell_history_init(void);
void	shell_history_shutdown(void);

#endif
