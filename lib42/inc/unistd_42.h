/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unistd_42.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:42:49 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 16:43:02 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNISTD_42_H
# define UNISTD_42_H

# include <stdbool.h>
# include <stdlib.h>

# define GETOPT_INVALID_ERR_FORMAT "%s: invalid option -- '%c'\n"
# define GETOPT_MULT_ERR_FORMAT "%s: option '%c' requires an argument\n"

# define OPT_INIT(o) ((o) = (t_opt){NULL, 1, 1, 1, -1, false})

typedef struct s_opt	t_opt;

struct	s_opt
{
	const char	*arg;
	size_t		end;
	unsigned	current_arg;
	unsigned	current_opt;
	int			unknown_opt;
	bool		print_errmsg;
};

int		ft_getopt(const char *const *av, const char *optstr, t_opt *opt);

#endif
