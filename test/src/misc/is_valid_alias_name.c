#include "misc.h"
#include "criterion/criterion.h"
#include "header.h"

TestSuite(is_valid_alias_name);

Test(is_valid_alias_name, length) {

	cr_assert(is_valid_alias_name("a\\", 1));
	cr_assert_not(is_valid_alias_name("a\\", 2));
	cr_assert_not(is_valid_alias_name("a\0", 2));
}

Test(is_valid_alias_name, valid) {

	cr_assert(is_valid_alias_name("a", 0));
	cr_assert(is_valid_alias_name("!%,@", 0));
	cr_assert(is_valid_alias_name("aA0", 0));
	cr_assert(is_valid_alias_name("0", 0));

}

Test(is_valid_alias_name, invalid) {

	char	buf[3] = "_x";
	char	chars[] = "'.<>\";:|-=+?/[]{}()*&^$#~`";

	buf[2] = '\0';
	for (unsigned long i = 0; i < sizeof(chars) - 1; i++) {

		buf[1] = chars[i];
		cr_assert_not(is_valid_alias_name(buf, 2));
	}
	cr_assert(is_valid_alias_name("", 0));
}
