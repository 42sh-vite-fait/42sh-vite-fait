/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 17:00:15 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 17:18:18 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPT_H
# define OPT_H

# include <stdbool.h>

# define OPT_NO_OPT			(1U << 0)
# define OPT_DEBUG_AST		(1U << 1)
# define OPT_DEBUG_LEXER	(1U << 2)
# define OPT_DEBUG_INPUT	(1U << 3)
# define OPT_DEBUG_EXEC		(1U << 4)
# define OPT_CMD_STRING		(1U << 5)
# define OPT_INTERACTIVE	(1U << 6)

void		opt_parse(int argc, const char *const *argv);
const char	*opt_get_command_line(void);
bool		opt_is_set(unsigned opt);

#endif
