/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansion.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 17:00:15 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 17:15:31 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_EXPANSION_H
# define HISTORY_EXPANSION_H

# include "str_42.h"
# include "ctype_42.h"
# include "history.h"
# include "quoting.h"

# define MAX_EXP 2048

enum	e_extype {
	E_TYPE_NUM,
	E_TYPE_BACK_NUM,
	E_TYPE_STRING
};

enum	e_state {
	E_START,
	E_STRING,
	E_NUM,
	E_BACK_NUM,
	E_FINISHED
};

typedef struct s_exp	t_exp;

struct	s_exp
{
	enum e_extype	type;
	t_string		string;
	size_t			n_back;
	size_t			offset;
	size_t			size;
};

size_t	identify_expansion(t_exp *outexp, t_string command, size_t i);
int		history_substitutions(t_string *command);
int		substitute(t_string *command, t_exp exp, t_string string, int dephase);
int		get_substitution(t_exp exp, t_string *b);
void	print_error(t_exp exp, t_string command);
void	free_data(t_exp *listexp, t_string *list, size_t expnum, size_t strnum);

#endif
