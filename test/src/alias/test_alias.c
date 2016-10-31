#include "header.h"
#include "criterion/criterion.h"

extern t_alias	g_alias;

static void		setup(void) {

	array_init(&g_alias.aliases, sizeof(t_string));
}

static void		teardown(void) {

	t_string	old;

	while (g_alias.aliases.len != 0)
	{
		array_pop(&g_alias.aliases, &old);
		string_shutdown(&old);
	}
	array_shutdown(&g_alias.aliases);
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

Test(alias, multiple_set) {

	t_string	aei_bar_aei;
	t_string	eio_bar_eio;
	t_string	iou_bar_iou;
	t_string	foo_bar_foo;
	t_string	fee_bar_fee;
	t_string	fas_bar_fas;
	t_string	pre_bar_pre;
	t_string	pra_bar_pra;
	t_string	pro_bar_pro;

	string_dup(&aei_bar_aei, "aei=bar_aei");
	string_dup(&eio_bar_eio, "eio=bar_eio");
	string_dup(&iou_bar_iou, "iou=bar_iou");
	string_dup(&foo_bar_foo, "foo=bar_foo");
	string_dup(&fee_bar_fee, "fee=bar_fee");
	string_dup(&fas_bar_fas, "fas=bar_fas");
	string_dup(&pre_bar_pre, "pre=bar_pre");
	string_dup(&pra_bar_pra, "pra=bar_pra");
	string_dup(&pro_bar_pro, "pro=bar_pro");

	cr_assert_eq(0, alias_set(&aei_bar_aei));
	cr_assert_eq(0, alias_set(&eio_bar_eio));
	cr_assert_eq(0, alias_set(&iou_bar_iou));
	cr_assert_eq(0, alias_set(&foo_bar_foo));
	cr_assert_eq(0, alias_set(&fee_bar_fee));
	cr_assert_eq(0, alias_set(&fas_bar_fas));
	cr_assert_eq(0, alias_set(&pre_bar_pre));
	cr_assert_eq(0, alias_set(&pra_bar_pra));
	cr_assert_eq(0, alias_set(&pro_bar_pro));
	{
		t_string	aei;
		t_string	eio;
		t_string	iou;
		t_string	foo;
		t_string	fee;
		t_string	fas;
		t_string	pre;
		t_string	pra;
		t_string	pro;

		string_dup(&aei, "aei");
		string_dup(&eio, "eio");
		string_dup(&iou, "iou");
		string_dup(&foo, "foo");
		string_dup(&fee, "fee");
		string_dup(&fas, "fas");
		string_dup(&pre, "pre");
		string_dup(&pra, "pra");
		string_dup(&pro, "pro");
		{
			const char	*value;

			value = alias_get_value(&aei);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_aei", value);

			value = alias_get_value(&eio);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_eio", value);

			value = alias_get_value(&iou);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_iou", value);

			value = alias_get_value(&foo);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_foo", value);

			value = alias_get_value(&fee);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_fee", value);

			value = alias_get_value(&fas);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_fas", value);

			value = alias_get_value(&pre);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_pre", value);

			value = alias_get_value(&pra);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_pra", value);

			value = alias_get_value(&pro);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_pro", value);
		}
		string_shutdown(&aei);
		string_shutdown(&eio);
		string_shutdown(&iou);
		string_shutdown(&foo);
		string_shutdown(&fee);
		string_shutdown(&fas);
		string_shutdown(&pre);
		string_shutdown(&pra);
		string_shutdown(&pro);
	}
}

Test(alias, multiple_set_random_order) {

	t_string	aei_bar_aei;
	t_string	eio_bar_eio;
	t_string	iou_bar_iou;
	t_string	foo_bar_foo;
	t_string	fee_bar_fee;
	t_string	fas_bar_fas;
	t_string	pre_bar_pre;
	t_string	pra_bar_pra;
	t_string	pro_bar_pro;

	string_dup(&aei_bar_aei, "aei=bar_aei");
	string_dup(&eio_bar_eio, "eio=bar_eio");
	string_dup(&iou_bar_iou, "iou=bar_iou");
	string_dup(&foo_bar_foo, "foo=bar_foo");
	string_dup(&fee_bar_fee, "fee=bar_fee");
	string_dup(&fas_bar_fas, "fas=bar_fas");
	string_dup(&pre_bar_pre, "pre=bar_pre");
	string_dup(&pra_bar_pra, "pra=bar_pra");
	string_dup(&pro_bar_pro, "pro=bar_pro");

	cr_assert_eq(0, alias_set(&eio_bar_eio));
	cr_assert_eq(0, alias_set(&fas_bar_fas));
	cr_assert_eq(0, alias_set(&pre_bar_pre));
	cr_assert_eq(0, alias_set(&pro_bar_pro));
	cr_assert_eq(0, alias_set(&pra_bar_pra));
	cr_assert_eq(0, alias_set(&aei_bar_aei));
	cr_assert_eq(0, alias_set(&foo_bar_foo));
	cr_assert_eq(0, alias_set(&iou_bar_iou));
	cr_assert_eq(0, alias_set(&fee_bar_fee));
	{
		t_string	aei;
		t_string	eio;
		t_string	iou;
		t_string	foo;
		t_string	fee;
		t_string	fas;
		t_string	pre;
		t_string	pra;
		t_string	pro;

		string_dup(&aei, "aei");
		string_dup(&eio, "eio");
		string_dup(&iou, "iou");
		string_dup(&foo, "foo");
		string_dup(&fee, "fee");
		string_dup(&fas, "fas");
		string_dup(&pre, "pre");
		string_dup(&pra, "pra");
		string_dup(&pro, "pro");
		{
			const char	*value;

			value = alias_get_value(&aei);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_aei", value);

			value = alias_get_value(&eio);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_eio", value);

			value = alias_get_value(&iou);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_iou", value);

			value = alias_get_value(&foo);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_foo", value);

			value = alias_get_value(&fee);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_fee", value);

			value = alias_get_value(&fas);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_fas", value);

			value = alias_get_value(&pre);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_pre", value);

			value = alias_get_value(&pra);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_pra", value);

			value = alias_get_value(&pro);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_pro", value);
		}
		string_shutdown(&aei);
		string_shutdown(&eio);
		string_shutdown(&iou);
		string_shutdown(&foo);
		string_shutdown(&fee);
		string_shutdown(&fas);
		string_shutdown(&pre);
		string_shutdown(&pra);
		string_shutdown(&pro);
	}
}

Test(alias, multiple_set_replace) {

	t_string	aei_bar_aei;
	t_string	eio_bar_eio;
	t_string	iou_bar_iou;
	t_string	foo_bar_foo;
	t_string	fee_bar_fee;
	t_string	fas_bar_fas;
	t_string	pre_bar_pre;
	t_string	pra_bar_pra;
	t_string	pro_bar_pro;

	string_dup(&aei_bar_aei, "aei=bar_aei");
	string_dup(&eio_bar_eio, "eio=bar_eio");
	string_dup(&iou_bar_iou, "iou=bar_iou");
	string_dup(&foo_bar_foo, "foo=bar_foo");
	string_dup(&fee_bar_fee, "fee=bar_fee");
	string_dup(&fas_bar_fas, "fas=bar_fas");
	string_dup(&pre_bar_pre, "pre=bar_pre");
	string_dup(&pra_bar_pra, "pra=bar_pra");
	string_dup(&pro_bar_pro, "pro=bar_pro");

	cr_assert_eq(0, alias_set(&aei_bar_aei));
	cr_assert_eq(0, alias_set(&eio_bar_eio));
	cr_assert_eq(0, alias_set(&iou_bar_iou));
	cr_assert_eq(0, alias_set(&foo_bar_foo));
	cr_assert_eq(0, alias_set(&fee_bar_fee));
	cr_assert_eq(0, alias_set(&fas_bar_fas));
	cr_assert_eq(0, alias_set(&pre_bar_pre));
	cr_assert_eq(0, alias_set(&pra_bar_pra));
	cr_assert_eq(0, alias_set(&pro_bar_pro));
	{
		t_string	aei;
		t_string	eio;
		t_string	iou;
		t_string	foo;
		t_string	fee;
		t_string	fas;
		t_string	pre;
		t_string	pra;
		t_string	pro;

		string_dup(&aei, "aei");
		string_dup(&eio, "eio");
		string_dup(&iou, "iou");
		string_dup(&foo, "foo");
		string_dup(&fee, "fee");
		string_dup(&fas, "fas");
		string_dup(&pre, "pre");
		string_dup(&pra, "pra");
		string_dup(&pro, "pro");
		{
			const char	*value;

			value = alias_get_value(&aei);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_aei", value);

			value = alias_get_value(&eio);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_eio", value);

			value = alias_get_value(&iou);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_iou", value);

			value = alias_get_value(&foo);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_foo", value);

			value = alias_get_value(&fee);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_fee", value);

			value = alias_get_value(&fas);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_fas", value);

			value = alias_get_value(&pre);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_pre", value);

			value = alias_get_value(&pra);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_pra", value);

			value = alias_get_value(&pro);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_pro", value);
		}

		t_string	aei_bar_aei2;
		t_string	eio_bar_eio2;
		t_string	iou_bar_iou2;
		t_string	foo_bar_foo2;
		t_string	fee_bar_fee2;
		t_string	fas_bar_fas2;
		t_string	pre_bar_pre2;
		t_string	pra_bar_pra2;
		t_string	pro_bar_pro2;

		string_dup(&aei_bar_aei2, "aei=bar_aei2");
		string_dup(&eio_bar_eio2, "eio=bar_eio2");
		string_dup(&iou_bar_iou2, "iou=bar_iou2");
		string_dup(&foo_bar_foo2, "foo=bar_foo2");
		string_dup(&fee_bar_fee2, "fee=bar_fee2");
		string_dup(&fas_bar_fas2, "fas=bar_fas2");
		string_dup(&pre_bar_pre2, "pre=bar_pre2");
		string_dup(&pra_bar_pra2, "pra=bar_pra2");
		string_dup(&pro_bar_pro2, "pro=bar_pro2");

		cr_assert_eq(0, alias_set(&aei_bar_aei2));
		cr_assert_eq(0, alias_set(&eio_bar_eio2));
		cr_assert_eq(0, alias_set(&iou_bar_iou2));
		cr_assert_eq(0, alias_set(&foo_bar_foo2));
		cr_assert_eq(0, alias_set(&fee_bar_fee2));
		cr_assert_eq(0, alias_set(&fas_bar_fas2));
		cr_assert_eq(0, alias_set(&pre_bar_pre2));
		cr_assert_eq(0, alias_set(&pra_bar_pra2));
		cr_assert_eq(0, alias_set(&pro_bar_pro2));
		{
			const char	*value;

			value = alias_get_value(&aei);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_aei2", value);

			value = alias_get_value(&eio);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_eio2", value);

			value = alias_get_value(&iou);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_iou2", value);

			value = alias_get_value(&foo);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_foo2", value);

			value = alias_get_value(&fee);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_fee2", value);

			value = alias_get_value(&fas);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_fas2", value);

			value = alias_get_value(&pre);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_pre2", value);

			value = alias_get_value(&pra);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_pra2", value);

			value = alias_get_value(&pro);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_pro2", value);
		}
		string_shutdown(&aei);
		string_shutdown(&eio);
		string_shutdown(&iou);
		string_shutdown(&foo);
		string_shutdown(&fee);
		string_shutdown(&fas);
		string_shutdown(&pre);
		string_shutdown(&pra);
		string_shutdown(&pro);
	}
}

Test(alias, multiple_set_unset_get) {

	t_string	aei_bar_aei;
	t_string	eio_bar_eio;
	t_string	iou_bar_iou;
	t_string	foo_bar_foo;
	t_string	fee_bar_fee;
	t_string	fas_bar_fas;
	t_string	pre_bar_pre;
	t_string	pra_bar_pra;
	t_string	pro_bar_pro;

	string_dup(&aei_bar_aei, "aei=bar_aei");
	string_dup(&eio_bar_eio, "eio=bar_eio");
	string_dup(&iou_bar_iou, "iou=bar_iou");
	string_dup(&foo_bar_foo, "foo=bar_foo");
	string_dup(&fee_bar_fee, "fee=bar_fee");
	string_dup(&fas_bar_fas, "fas=bar_fas");
	string_dup(&pre_bar_pre, "pre=bar_pre");
	string_dup(&pra_bar_pra, "pra=bar_pra");
	string_dup(&pro_bar_pro, "pro=bar_pro");

	cr_assert_eq(0, alias_set(&aei_bar_aei));
	cr_assert_eq(0, alias_set(&eio_bar_eio));
	cr_assert_eq(0, alias_set(&iou_bar_iou));
	cr_assert_eq(0, alias_set(&foo_bar_foo));
	cr_assert_eq(0, alias_set(&fee_bar_fee));
	cr_assert_eq(0, alias_set(&fas_bar_fas));
	cr_assert_eq(0, alias_set(&pre_bar_pre));
	cr_assert_eq(0, alias_set(&pra_bar_pra));
	cr_assert_eq(0, alias_set(&pro_bar_pro));
	{
		t_string	aei;
		t_string	eio;
		t_string	iou;
		t_string	foo;
		t_string	fee;
		t_string	fas;
		t_string	pre;
		t_string	pra;
		t_string	pro;

		string_dup(&aei, "aei");
		string_dup(&eio, "eio");
		string_dup(&iou, "iou");
		string_dup(&foo, "foo");
		string_dup(&fee, "fee");
		string_dup(&fas, "fas");
		string_dup(&pre, "pre");
		string_dup(&pra, "pra");
		string_dup(&pro, "pro");
		{
			const char	*value;

			value = alias_get_value(&aei);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_aei", value);

			value = alias_get_value(&eio);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_eio", value);

			value = alias_get_value(&iou);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_iou", value);

			value = alias_get_value(&foo);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_foo", value);

			value = alias_get_value(&fee);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_fee", value);

			value = alias_get_value(&fas);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_fas", value);

			value = alias_get_value(&pre);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_pre", value);

			value = alias_get_value(&pra);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_pra", value);

			value = alias_get_value(&pro);
			cr_assert_not_null(value);
			cr_assert_str_eq("bar_pro", value);
		}
		{
			cr_assert_eq(0, alias_unset(&aei));
			cr_assert_eq(0, alias_unset(&eio));
			cr_assert_eq(0, alias_unset(&iou));
			cr_assert_eq(0, alias_unset(&foo));
			cr_assert_eq(0, alias_unset(&fee));
			cr_assert_eq(0, alias_unset(&fas));
			cr_assert_eq(0, alias_unset(&pre));
			cr_assert_eq(0, alias_unset(&pra));
			cr_assert_eq(0, alias_unset(&pro));
		}
		{
			const char	*value;

			value = alias_get_value(&aei);
			cr_assert_null(value);

			value = alias_get_value(&eio);
			cr_assert_null(value);

			value = alias_get_value(&iou);
			cr_assert_null(value);

			value = alias_get_value(&foo);
			cr_assert_null(value);

			value = alias_get_value(&fee);
			cr_assert_null(value);

			value = alias_get_value(&fas);
			cr_assert_null(value);

			value = alias_get_value(&pre);
			cr_assert_null(value);

			value = alias_get_value(&pra);
			cr_assert_null(value);

			value = alias_get_value(&pro);
			cr_assert_null(value);
		}

		string_shutdown(&aei);
		string_shutdown(&eio);
		string_shutdown(&iou);
		string_shutdown(&foo);
		string_shutdown(&fee);
		string_shutdown(&fas);
		string_shutdown(&pre);
		string_shutdown(&pra);
		string_shutdown(&pro);
	}
}
