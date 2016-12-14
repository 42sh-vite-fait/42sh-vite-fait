#ifndef ERRORS_H
# define ERRORS_H

enum e_errors {
	NO_ERROR,
	ERR_MALLOC,

	// Variable module
	ERR_VAR_NOT_FOUND,
	ERR_VAR_RDONLY
};

void	errors_init(void);

#endif