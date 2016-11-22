#include "header.h"
#include "criterion/criterion.h"

void		setup(void)
{
	alias_init();
}

void		teardown(void)
{
	alias_shutdown();
}

TestSuite(builtin_alias, .init = setup, .fini = teardown);

Test(builtin_alias, display_one_alias) {

	int			fildes[2];
	int			oldout;
	int			newout;
	t_string	command_output;

	{ // setup stdout redirection
		cr_assert_neq(-1, pipe(fildes));
		oldout = dup(1);
		close(1);
		newout = dup(fildes[1]);
	}

	{
		char	*opts[] = { "alias", "hi=salut", NULL };
		cr_assert_eq(0, builtin_alias(2, opts));
	}

	{
		char	*opts[] = { "alias", "hi", NULL };
		cr_assert_eq(0, builtin_alias(2, opts));
	}

	string_read_from_fd(&command_output, fildes[0]);

	{ // stop stdout redirection
		close(fildes[1]);
		close(1);
		newout = dup(oldout);
		close(oldout);
	}

	cr_assert_str_eq("alias hi='salut'\n", command_output.str);
	string_shutdown(&command_output);
}
