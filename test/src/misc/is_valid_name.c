#include "misc.h"
#include "criterion/criterion.h"
#include "header.h"

TestSuite(is_valid_name);

Test(is_valid_name, first_character_not_a_digit) {

	cr_assert_not(is_valid_name("0abcd", 1));
	cr_assert_not(is_valid_name("0abcd", 2));
}

Test(is_valid_name, length) {

	cr_assert(is_valid_name("a\\", 0));
	cr_assert(is_valid_name("a\\", 1));
	cr_assert_not(is_valid_name("a\\", 2));
	cr_assert_not(is_valid_name("a\0", 2));
}

Test(is_valid_name, legal_chars) {

	cr_assert(is_valid_name("_foo42BAR", 0));
	cr_assert(is_valid_name("_", 0));
	cr_assert(is_valid_name("a", 0));
}

Test(is_valid_name, illegal_chars) {

	char	buf[3] = "_x";
	char	chars[] = "',.<>\";:|-=+?/[]{}()*&^%$#@!~`";

	buf[2] = '\0';
	for (unsigned long i = 0; i < sizeof(chars) - 1; i++) {

		buf[1] = chars[i];
		cr_assert_not(is_valid_name(buf, 2));
	}
	cr_assert(is_valid_name("", 0));
}
