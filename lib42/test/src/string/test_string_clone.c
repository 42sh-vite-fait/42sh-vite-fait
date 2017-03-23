#include "header.h"

static void	test_00_string_clone_Simple(void)
{
	t_string	origin;
	t_string	cp;

	string_init_dup(&origin, "Hello World!");
	string_clone(&cp, &origin);

	v_assert_size_t(origin.len, ==, cp.len);
	v_assert_str(origin.str, cp.str);
	v_assert_ptr(origin.str, !=, cp.str);
	v_assert_ptr(&origin, !=, &cp);

	string_shutdown(&origin);
	string_shutdown(&cp);
	VTS;
}

static void	test_01_string_clone_Empty(void)
{
	t_string	origin;
	t_string	cp;

	string_init(&origin);
	string_clone(&cp, &origin);

	v_assert_size_t(origin.len, ==, cp.len);
	v_assert_str(origin.str, cp.str);
	v_assert_ptr(origin.str, !=, cp.str);
	v_assert_ptr(&origin, !=, &cp);

	string_shutdown(&origin);
	string_shutdown(&cp);
	VTS;
}

void	suite_string_clone(void)
{
	test_00_string_clone_Simple();
	test_01_string_clone_Empty();

	VSS;
}
