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

	char *foo_bar = ft_strdup("foo=bar");

	cr_assert_eq(0, alias_set(foo_bar));
}

Test(alias, simple_set_check_not_duplicated) {

	char		*foo_bar = ft_strdup("foo=bar");
	char		*foo = "foo";
	const char	*value;

	cr_assert_eq(0, alias_set(foo_bar));

	foo_bar[5]= 'o';

	value = alias_get_value(foo);
	cr_assert_not_null(value);
	cr_assert_str_eq("bor", value);
}

Test(alias, simple_set_get) {

	char		*foo_bar = ft_strdup("foo=bar");
	char		*foo_baz = ft_strdup("foo=baz");
	char		*foo = "foo";
	const char	*value;

	cr_assert_eq(0, alias_set(foo_bar));

	value = alias_get_value(foo);
	cr_assert_not_null(value);
	cr_assert_str_eq("bar", value);

	cr_assert_eq(0, alias_set(foo_baz));

	value = alias_get_value(foo);
	cr_assert_not_null(value);
	cr_assert_str_eq("baz", value);
}

Test(alias, simple_set_get_unset_get) {

	char		*foo_bar = ft_strdup("foo=bar");
	char		*foo = "foo";
	const char	*value;

	cr_assert_eq(0, alias_set(foo_bar));

	value = alias_get_value(foo);
	cr_assert_not_null(value);
	cr_assert_str_eq("bar", value);

	cr_assert_eq(0, alias_unset(foo));

	value = alias_get_value(foo);
	cr_assert_null(value);
}

Test(alias, simple_unset_non_existent) {

	char		*foo_bar = ft_strdup("foo=bar");
	char		*foo = "foo";
	char		*fast = "fast";
	const char	*value;

	cr_assert_eq(0, alias_set(foo_bar));

	value = alias_get_value(foo);
	cr_assert_not_null(value);
	cr_assert_str_eq("bar", value);

	cr_assert_eq(-1, alias_unset(fast));

	value = alias_get_value(foo);
	cr_assert_not_null(value);
	cr_assert_str_eq("bar", value);
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
	char		*names_values[9] = {
		ft_strdup("aei=bar_aei"),
		ft_strdup("eio=bar_eio"),
		ft_strdup("iou=bar_iou"),
		ft_strdup("foo=bar_foo"),
		ft_strdup("fee=bar_fee"),
		ft_strdup("fas=bar_fas"),
		ft_strdup("pre=bar_pre"),
		ft_strdup("pra=bar_pra"),
		ft_strdup("pro=bar_pro")
	};
	const char	*names[9] = {
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
	const char	*values[9] = {
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
		const char	*value;

		cr_assert_eq(0, alias_set(names_values[i]));

		value = alias_get_value(names[i]);
		cr_assert_not_null(value);
		cr_assert_str_eq(values[i], value);
	}
}

Test(alias, multiple_set_random_order) {

	t_string	name_value;
	char		*names_values[9] = {
		ft_strdup("aei=bar_aei"),
		ft_strdup("eio=bar_eio"),
		ft_strdup("iou=bar_iou"),
		ft_strdup("foo=bar_foo"),
		ft_strdup("fee=bar_fee"),
		ft_strdup("fas=bar_fas"),
		ft_strdup("pre=bar_pre"),
		ft_strdup("pra=bar_pra"),
		ft_strdup("pro=bar_pro")
	};
	const char	*names[9] = {
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
	const char	*values[9] = {
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
		cr_assert_eq(0, alias_set(names_values[i]));
	}

	for (size_t i = 0; i < 9; ++i) {
		const char	*value;

		value = alias_get_value(names[i]);
		cr_assert_not_null(value);
		cr_assert_str_eq(values[i], value);
	}
}

Test(alias, multiple_set_replace) {

	t_string	name_value;
	char		*names_values[9] = {
		ft_strdup("aei=bar_aei"),
		ft_strdup("eio=bar_eio"),
		ft_strdup("iou=bar_iou"),
		ft_strdup("foo=bar_foo"),
		ft_strdup("fee=bar_fee"),
		ft_strdup("fas=bar_fas"),
		ft_strdup("pre=bar_pre"),
		ft_strdup("pra=bar_pra"),
		ft_strdup("pro=bar_pro")
	};
	const char	*names[9] = {
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
	const char	*values[9] = {
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
		const char	*value;

		cr_assert_eq(0, alias_set(names_values[i]));

		value = alias_get_value(names[i]);
		cr_assert_not_null(value);
		cr_assert_str_eq(values[i], value);
	}

	t_string	name_value2;
	char		*names_values2[9] = {
		ft_strdup("aei=bar_aei2"),
		ft_strdup("eio=bar_eio2"),
		ft_strdup("iou=bar_iou2"),
		ft_strdup("foo=bar_foo2"),
		ft_strdup("fee=bar_fee2"),
		ft_strdup("fas=bar_fas2"),
		ft_strdup("pre=bar_pre2"),
		ft_strdup("pra=bar_pra2"),
		ft_strdup("pro=bar_pro2")
	};
	const char	*values2[9] = {
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
		const char	*value;

		cr_assert_eq(0, alias_set(names_values2[i]));

		value = alias_get_value(names[i]);
		cr_assert_not_null(value);
		cr_assert_str_eq(values2[i], value);
	}
}

Test(alias, multiple_set_unset_get) {

	t_string	name_value;
	char		*names_values[9] = {
		ft_strdup("aei=bar_aei"),
		ft_strdup("eio=bar_eio"),
		ft_strdup("iou=bar_iou"),
		ft_strdup("foo=bar_foo"),
		ft_strdup("fee=bar_fee"),
		ft_strdup("fas=bar_fas"),
		ft_strdup("pre=bar_pre"),
		ft_strdup("pra=bar_pra"),
		ft_strdup("pro=bar_pro")
	};
	const char	*names[9] = {
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
	const char	*values[9] = {
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
		cr_assert_eq(0, alias_set(names_values[i]));
	}

	for (size_t i = 0; i < 9; ++i) {
		const char	*value;

		value = alias_get_value(names[i]);
		cr_assert_not_null(value);
		cr_assert_str_eq(values[i], value);

		cr_assert_eq(0, alias_unset(names[i]));
	}

	for (size_t i = 0; i < 9; ++i) {
		const char	*value;

		value = alias_get_value(names[i]);
		cr_assert_null(value);
	}
}

Test(alias, clear_get) {

	t_string	name_value;
	char		*names_values[9] = {
		ft_strdup("aei=bar_aei"),
		ft_strdup("eio=bar_eio"),
		ft_strdup("iou=bar_iou"),
		ft_strdup("foo=bar_foo"),
		ft_strdup("fee=bar_fee"),
		ft_strdup("fas=bar_fas"),
		ft_strdup("pre=bar_pre"),
		ft_strdup("pra=bar_pra"),
		ft_strdup("pro=bar_pro")
	};
	const char	*names[9] = {
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
	const char	*values[9] = {
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
		cr_assert_eq(0, alias_set(names_values[i]));
	}

	alias_clear();

	for (size_t i = 0; i < 9; ++i) {
		const char	*value;

		value = alias_get_value(names[i]);
		cr_assert_null(value);
	}
}

Test(alias, get_all_empty) {

	cr_assert_eq(0, alias_get_all()->len);
}

Test(alias, get_all) {

	char			*foo_bar = ft_strdup("foo=bar");
	char			*bar_baz = ft_strdup("bar=baz");
	const t_array	*all_aliases;

	cr_assert_eq(0, alias_set(foo_bar));
	cr_assert_eq(0, alias_set(bar_baz));

	all_aliases = alias_get_all();

	cr_assert_str_eq(foo_bar, ((t_string*)array_get_at(all_aliases, 0))->str);
	cr_assert_str_eq(bar_baz, ((t_string*)array_get_at(all_aliases, 1))->str);
}
