#include "header.h"
#include "criterion/criterion.h"
#include "criterion/redirect.h"
#include "builtins.h"

#define TRUE 1
#define FALSE 0

TestSuite(builtins_utils);

#define CHECK_BUILTIN(NAME, SIZE, SHALL_BE_FOUND) {			\
	cr_assert((is_builtin(NAME, SIZE) == SHALL_BE_FOUND));	\
}

Test(builtins_utils, simple_echo) {
	CHECK_BUILTIN("echo", 4, TRUE); }

Test(builtins_utils, echo_minus_one_letter) {
	CHECK_BUILTIN("ech", 3, FALSE); }

Test(builtins_utils, echo_plus_one_letter) {
	CHECK_BUILTIN("echoo", 5, FALSE); }

Test(builtins_utils, echo_plus_garbage_but_right_size) {
	CHECK_BUILTIN("echoqwerit", 4, TRUE); }

Test(builtins_utils, empty_string_size_0) {
	CHECK_BUILTIN("", 0, FALSE); }

Test(builtins_utils, empty_string_size_1) {
	CHECK_BUILTIN("", 1, FALSE); }

Test(builtins_utils, setenv) {
	CHECK_BUILTIN("setenv", 6, TRUE); }
