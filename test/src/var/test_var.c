/*
** The vocabulary used in the following test names is not accurate. For more info see:
** https://github.com/itheof/42sh-posix/issues/54#issuecomment-265735118
*/

#include "criterion/criterion.h"
#include "header.h"

extern t_array	g_environ_priv;
extern char		**g_environ;

TestSuite(var, .init=var_init, .fini=var_shutdown);

Test(var, value_with_multiple_names) {

	const char	*val;

	cr_assert_eq(var_set("", "empty", 0U), NO_ERROR);
	cr_assert_eq(var_set("namedgecase", "lul", 0U), NO_ERROR);
	cr_assert_eq(var_set("name", "value", 0U), NO_ERROR);
	cr_assert_eq(var_get("name", &val), NO_ERROR);
	cr_assert_str_eq(val, "value");
	cr_assert_eq(var_get("", &val), NO_ERROR);
	cr_assert_str_eq(val, "empty");
	cr_assert_eq(var_get("namedgecase", &val), NO_ERROR);
	cr_assert_str_eq(val, "lul");
}

Test(var, get_unset_variable) {

	const char	*val;

	cr_assert_eq(var_get("?", &val), ERR_VAR_NOT_FOUND );
	cr_assert_null(val);
	cr_assert_eq(var_get("", &val), ERR_VAR_NOT_FOUND);
	cr_assert_null(val);
}

Test(var, null_value) {

	const char	*val;

	cr_assert_eq(var_set("name", NULL, 0U), NO_ERROR);
	cr_assert_eq(var_get("name", &val), NO_ERROR);
	cr_assert_eq(val, NULL);
}

Test(var, set_override_value) {

	const char	*val;

	var_set("foo", "bar", 0U);
	cr_assert_eq(var_set("foo", "baz", 0U), NO_ERROR);
	cr_assert_eq(var_get("foo", &val), NO_ERROR);
	cr_assert_str_eq(val, "baz");

	var_set("null", NULL, 0U);
	cr_assert_eq(var_set("null", "mmf", 0U), NO_ERROR);
	cr_assert_eq(var_get("null", &val), NO_ERROR);
	cr_assert_str_eq(val, "mmf");
}

Test(var, can_not_override_readonly_value) {

	const char	*val;
	var_set("ro", NULL, VAR_ATTR_RDONLY);
	cr_assert_eq(var_set("ro", "val", 0U), ERR_VAR_RDONLY);
	cr_assert_eq(var_get("ro", &val), NO_ERROR);
	cr_assert_null(val);
}

Test(var, no_attr_set_if_assignment_failed) {

	const char	*val;

	var_set("ro", "abcd", VAR_ATTR_RDONLY);
	cr_assert_eq(var_set("ro", "newval", VAR_ATTR_EXPORT), ERR_VAR_RDONLY);
	cr_assert_null(*g_environ);
}

Test(var, g_environ_updated) {

	var_set("public", "flag", VAR_ATTR_EXPORT);
	cr_assert_str_eq(*g_environ, "public=flag");
	var_unset("public");
	cr_assert_null(*g_environ);

	var_set("nullpublic", NULL, VAR_ATTR_EXPORT);
	cr_assert_null(*g_environ);
	var_set("nullpublic", "lol", 0U);
	cr_assert_str_eq(*g_environ, "nullpublic=lol");
	var_unset("nullpublic");
	cr_assert_null(*g_environ);
}

Test(var, g_environ_not_updated) {

	var_set("nullpublic", NULL, VAR_ATTR_EXPORT);
	cr_assert_null(*g_environ);
	cr_assert_eq(var_unset("nullpublic"), NO_ERROR);
	cr_assert_null(*g_environ);
	var_set("nullpublic", NULL, VAR_ATTR_RDONLY);
	var_set("nullpublic", "failedassignement", 0U);
	cr_assert_null(*g_environ);

	var_set("null", NULL, VAR_ATTR_EXPORT);
	cr_assert_eq(var_unset("null"), NO_ERROR);
	cr_assert_null(*g_environ);

	var_set("private", "noflag", 0U);
	cr_assert_null(*g_environ);
	var_set("private", NULL, VAR_ATTR_RDONLY | VAR_ATTR_EXPORT);
	cr_assert_not_null(*g_environ);
	var_unset("private");
	cr_assert_not_null(*g_environ);
}

Test(var, cannot_unset_readonly_variable) {

	const char	*val;

	var_set("ro", "val", VAR_ATTR_RDONLY);
	cr_assert_eq(var_unset("ro"), ERR_VAR_RDONLY);
	cr_assert_eq(var_get("ro", &val), NO_ERROR);
	cr_assert_str_eq(val, "val");
	// assert ro attr is still present
	cr_assert_eq(var_unset("ro"), ERR_VAR_RDONLY);
}

Test(var, unset_clears_entry) {

	const char	*val;

	var_set("bar", "foo", VAR_ATTR_EXPORT);
	cr_assert_eq(var_unset("bar"), NO_ERROR);
	cr_assert_eq(var_get("bar", &val), ERR_VAR_NOT_FOUND);
	var_set("bar", "baz", 0U);
	cr_assert_null(*g_environ);// asserts export attr does not remain
}

Test(var, unset_not_found) {

	cr_assert_eq(var_unset("notfound"), ERR_VAR_NOT_FOUND);
}

Test(var, attrs_append) {

	const char	*val;

	cr_assert_eq(var_set("public", "val1", VAR_ATTR_EXPORT), NO_ERROR);
	cr_assert_eq(var_set("public", "val2", VAR_ATTR_RDONLY), NO_ERROR);
	cr_assert_str_eq(*g_environ, "public=val2");
	cr_assert_eq(var_set("public", NULL, 0U), NO_ERROR);
	cr_assert_eq(var_set("public", NULL, VAR_ATTR_EXPORT), NO_ERROR);
	cr_assert_eq(var_set("public", NULL, VAR_ATTR_RDONLY), NO_ERROR);
	cr_assert_not_null(*g_environ);
	cr_assert_eq(var_set("public", "val3", 0U), ERR_VAR_RDONLY);

	// can append attrs to a readonly var
	cr_assert_eq(var_set("ro", "val1", VAR_ATTR_RDONLY), NO_ERROR);
	cr_assert_eq(var_set("ro", NULL, VAR_ATTR_EXPORT), NO_ERROR);
	cr_assert_not_null(*g_environ);
	cr_assert_not_null(*(g_environ + 1));

	// can combine attrs
	cr_assert_eq(var_set("bothflagged", "val4", VAR_ATTR_RDONLY | VAR_ATTR_EXPORT), NO_ERROR);
	cr_assert_not_null(*g_environ);
	cr_assert_not_null(*(g_environ + 1));
	cr_assert_not_null(*(g_environ + 2));
	cr_assert_eq(var_set("bothflagged", "val3", 0U), ERR_VAR_RDONLY);
}
