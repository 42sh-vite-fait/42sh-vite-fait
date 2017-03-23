#ifndef UNISTD_42_H
# define UNISTD_42_H

# include <stdbool.h>
# include <stdlib.h>

# define GETOPT_INVALID_ERR_FORMAT "%s: invalid option -- '%c'\n"
# define GETOPT_MULT_ERR_FORMAT "%s: option '%c' requires an argument\n"


# define OPT_INIT(o) ((o) = (t_opt){NULL, 1, 1, -1, false})

typedef struct s_opt	t_opt;

struct	s_opt
{
	const char	*arg;
	size_t		current;
	size_t		end;
	int			unknown_opt;
	bool		print_errmsg;
};

int	ft_getopt(const char *const *av, const char *optstr, t_opt *opt);

#endif
