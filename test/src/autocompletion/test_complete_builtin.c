#include "header.h"
#include "criterion/criterion.h"

TestSuite(builtins_autocompletion);

// First is the incomplete command, next are expected matches
#define COMPLETE(...) {									\
	t_array matches;									\
	const char *args[] = {__VA_ARGS__};					\
	const char *cmd = args[0];							\
	const char **expected = args + 1;					\
	size_t expected_size = sizeof(args) / 8 - 1;		\
	char *match;										\
	array_init(&matches, sizeof(char *));				\
	complete_builtin(&matches, cmd);					\
	cr_assert(matches.len == expected_size);			\
	for (size_t i=0;i<matches.len;i++) {				\
		match = *(char **)array_get_at(&matches, i);	\
		cr_assert_str_eq(match, expected[i]); }}

Test(builtins_autocompletion, some_completions) {
	COMPLETE("e", "echo", "env", "exit");
}

Test(builtins_autocompletion, exact_completion) {
	COMPLETE("setenv", "setenv");
}

Test(builtins_autocompletion, no_completion) {
	COMPLETE("qwerty");
}
