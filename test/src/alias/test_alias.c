#include "header.h"
#include "criterion/criterion.h"

extern t_alias	g_alias;

static void		setup(void) {

	array_init(&g_alias, sizeof(t_string));
}

static void		teardown(void) {

	t_string	old;

	while (g_alias.len != 0)
	{
		array_pop(&g_alias, &old);
		string_shutdown(&old);
	}
	array_shutdown(&g_alias);
}

TestSuite(alias, .init = setup, .fini = teardown);

Test(alias, simple_set) {

	t_string	foo_bar;

	string_dup(&foo_bar, "foo=bar");

	cr_assert_eq(0, alias_set(&foo_bar));
}

Test(alias, simple_set_check_not_duplicated) {

	t_string	foo_bar;
	t_string	foo;
	const char	*value;

	string_dup(&foo_bar, "foo=bar");

	cr_assert_eq(0, alias_set(&foo_bar));

	cr_assert_not_null(string_cat(&foo_bar, "-foo"));

	string_dup(&foo, "foo");
	{
		value = alias_get_value(&foo);
		cr_assert_not_null(value);
		cr_assert_str_eq("bar-foo", value);
	}
	string_shutdown(&foo);
}

Test(alias, simple_set_get) {

	t_string	foo_bar;
	t_string	foo;
	const char	*value;

	string_dup(&foo_bar, "foo=bar");

	cr_assert_eq(0, alias_set(&foo_bar));

	string_dup(&foo, "foo");
	{
		value = alias_get_value(&foo);
		cr_assert_not_null(value);
		cr_assert_str_eq("bar", value);
	}
	string_shutdown(&foo);
}


Test(alias, simple_set_get_unset_get) {

	t_string	foo_bar;
	t_string	foo;
	const char	*value;

	string_dup(&foo_bar, "foo=bar");

	cr_assert_eq(0, alias_set(&foo_bar));

	string_dup(&foo, "foo");
	{
		value = alias_get_value(&foo);
		cr_assert_not_null(value);
		cr_assert_str_eq("bar", value);
	}
	{
		cr_assert_eq(0, alias_unset(&foo));
	}
	{
		value = alias_get_value(&foo);
		cr_assert_null(value);
	}
	string_shutdown(&foo);
}

Test(alias, simple_unset_non_existent) {

	t_string	foo_bar;
	t_string	foo;
	const char	*value;

	string_dup(&foo_bar, "foo=bar");

	cr_assert_eq(0, alias_set(&foo_bar));

	string_dup(&foo, "foo");
	{
		value = alias_get_value(&foo);
		cr_assert_not_null(value);
		cr_assert_str_eq("bar", value);
	}
	{
		t_string	fast;

		string_dup(&fast, "fast");
		cr_assert_eq(-1, alias_unset(&fast));
		string_shutdown(&fast);
	}
	{
		value = alias_get_value(&foo);
		cr_assert_not_null(value);
		cr_assert_str_eq("bar", value);
	}
	string_shutdown(&foo);
}

static void		display_aliases(void)
{
	printf("\n[START ALIASES]\n");
	for (size_t i = 0; i < g_alias.len; ++i)
	{
		printf("%s\n", ((t_string*)array_get_at(&g_alias, i))->str);
	}
	printf("[END ALIASES]\n\n");
}

Test(alias, multiple_set) {

	t_string	name_value;
	const char	*names_values_str[9] = {
		"aei=bar_aei",
		"eio=bar_eio",
		"iou=bar_iou",
		"foo=bar_foo",
		"fee=bar_fee",
		"fas=bar_fas",
		"pre=bar_pre",
		"pra=bar_pra",
		"pro=bar_pro"
	};
	const char	*names_str[9] = {
		"aei",
		"eio",
		"iou",
		"foo",
		"fee",
		"fas",
		"pre",
		"pra",
		"pro"
	};
	const char	*values_str[9] = {
		"bar_aei",
		"bar_eio",
		"bar_iou",
		"bar_foo",
		"bar_fee",
		"bar_fas",
		"bar_pre",
		"bar_pra",
		"bar_pro"
	};

	for (size_t i = 0; i < 9; ++i) {

		t_string	name;
		const char	*value;

		string_dup(&name_value, names_values_str[i]);
		cr_assert_eq(0, alias_set(&name_value));

		string_dup(&name, names_str[i]);

		value = alias_get_value(&name);
		cr_assert_not_null(value);
		cr_assert_str_eq(values_str[i], value);

		string_shutdown(&name);
	}
}

Test(alias, multiple_set_random_order) {

	t_string	name_value;
	const char	*names_values_str[9] = {
		"aei=bar_aei",
		"eio=bar_eio",
		"iou=bar_iou",
		"foo=bar_foo",
		"fee=bar_fee",
		"fas=bar_fas",
		"pre=bar_pre",
		"pra=bar_pra",
		"pro=bar_pro"
	};
	const char	*names_str[9] = {
		"fee",
		"pra",
		"pre",
		"iou",
		"aei",
		"foo",
		"pro",
		"eio",
		"fas",
	};
	const char	*values_str[9] = {
		"bar_fee",
		"bar_pra",
		"bar_pre",
		"bar_iou",
		"bar_aei",
		"bar_foo",
		"bar_pro",
		"bar_eio",
		"bar_fas",
	};

	for (size_t i = 0; i < 9; ++i) {
		string_dup(&name_value, names_values_str[i]);
		cr_assert_eq(0, alias_set(&name_value));
	}

	for (size_t i = 0; i < 9; ++i) {

		t_string	name;
		const char	*value;

		string_dup(&name, names_str[i]);

		value = alias_get_value(&name);
		cr_assert_not_null(value);
		cr_assert_str_eq(values_str[i], value);

		string_shutdown(&name);
	}
}

Test(alias, multiple_set_replace) {

	t_string	name_value;
	const char	*names_values_str[9] = {
		"aei=bar_aei",
		"eio=bar_eio",
		"iou=bar_iou",
		"foo=bar_foo",
		"fee=bar_fee",
		"fas=bar_fas",
		"pre=bar_pre",
		"pra=bar_pra",
		"pro=bar_pro"
	};
	const char	*names_str[9] = {
		"aei",
		"eio",
		"iou",
		"foo",
		"fee",
		"fas",
		"pre",
		"pra",
		"pro"
	};
	const char	*values_str[9] = {
		"bar_aei",
		"bar_eio",
		"bar_iou",
		"bar_foo",
		"bar_fee",
		"bar_fas",
		"bar_pre",
		"bar_pra",
		"bar_pro"
	};

	for (size_t i = 0; i < 9; ++i) {

		t_string	name;
		const char	*value;

		string_dup(&name_value, names_values_str[i]);
		cr_assert_eq(0, alias_set(&name_value));

		string_dup(&name, names_str[i]);

		value = alias_get_value(&name);
		cr_assert_not_null(value);
		cr_assert_str_eq(values_str[i], value);

		string_shutdown(&name);
	}

	t_string	name_value2;
	const char	*names_values_str2[9] = {
		"aei=bar_aei2",
		"eio=bar_eio2",
		"iou=bar_iou2",
		"foo=bar_foo2",
		"fee=bar_fee2",
		"fas=bar_fas2",
		"pre=bar_pre2",
		"pra=bar_pra2",
		"pro=bar_pro2"
	};
	const char	*values_str2[9] = {
		"bar_aei2",
		"bar_eio2",
		"bar_iou2",
		"bar_foo2",
		"bar_fee2",
		"bar_fas2",
		"bar_pre2",
		"bar_pra2",
		"bar_pro2"
	};

	for (size_t i = 0; i < 9; ++i) {

		t_string	name;
		const char	*value;

		string_dup(&name_value2, names_values_str2[i]);
		cr_assert_eq(0, alias_set(&name_value2));

		string_dup(&name, names_str[i]);

		value = alias_get_value(&name);
		cr_assert_not_null(value);
		cr_assert_str_eq(values_str2[i], value);

		string_shutdown(&name);
	}
}

Test(alias, multiple_set_unset_get) {

	t_string	name_value;
	const char	*names_values_str[9] = {
		"aei=bar_aei",
		"eio=bar_eio",
		"iou=bar_iou",
		"foo=bar_foo",
		"fee=bar_fee",
		"fas=bar_fas",
		"pre=bar_pre",
		"pra=bar_pra",
		"pro=bar_pro"
	};
	const char	*names_str[9] = {
		"fee",
		"pra",
		"pre",
		"iou",
		"aei",
		"foo",
		"pro",
		"eio",
		"fas",
	};
	const char	*values_str[9] = {
		"bar_fee",
		"bar_pra",
		"bar_pre",
		"bar_iou",
		"bar_aei",
		"bar_foo",
		"bar_pro",
		"bar_eio",
		"bar_fas",
	};

	for (size_t i = 0; i < 9; ++i) {
		string_dup(&name_value, names_values_str[i]);
		cr_assert_eq(0, alias_set(&name_value));
	}

	for (size_t i = 0; i < 9; ++i) {

		t_string	name;
		const char	*value;

		string_dup(&name, names_str[i]);

		value = alias_get_value(&name);
		cr_assert_not_null(value);
		cr_assert_str_eq(values_str[i], value);

		cr_assert_eq(0, alias_unset(&name));

		string_shutdown(&name);
	}

	for (size_t i = 0; i < 9; ++i) {

		t_string	name;
		const char	*value;

		string_dup(&name, names_str[i]);

		value = alias_get_value(&name);
		cr_assert_null(value);

		string_shutdown(&name);
	}
}
