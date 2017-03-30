/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 17:00:15 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 17:30:36 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <errno.h>
# include <sys/errno.h>

# define BIN_NAME 	"42sh"
# define ERROR_ 		(-1)
# define OK_ 			(0)
# define CMD_DROP_ 		(1)
# define CMD_INVALID_ 	(2)
# define CMD_EOF_ 		(3)

void	error_set_context(const char *format, ...);
void	error_print(const char *module_name);

#endif
