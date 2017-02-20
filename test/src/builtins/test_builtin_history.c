#include "header.h"
#include "criterion/criterion.h"
#include "criterion/redirect.h"
#include "builtins.h"

TestSuite(builtin_history);

#define ARGS(A) (char *[]){A}, sizeof ((char *[]){A})

#define ARRAY(...) ((char *[]){"history", __VA_ARGS__ NULL})
#define ARRAY_ELEMS(A) (sizeof(A) / sizeof(*A) - 1)
#define CALL_HISTORY(...) builtin_history(ARRAY_ELEMS(ARRAY(__VA_ARGS__)), ARRAY(__VA_ARGS__))

#define POPULATE_HISTORY(SIZE, ...) {					\
	history_init(SIZE);									\
	char const *args[] = {__VA_ARGS__};					\
	t_string str;										\
	for (size_t i=0;i<=ARRAY_ELEMS(args);i++) {			\
		history_add(string_init_dup(&str, args[i])); }	\
	}

#define QUICK_CHECK_WITH_RANGE(SIZE, NBR, FIRST, LAST, ...) {		\
	history_init(SIZE);												\
	t_string str;													\
	for (size_t i=1;i<=NBR;i++) {									\
		history_add(string_init_dup(&str, ft_utoa_base(i, 10))); }	\
	char *expected = NULL;											\
	char *tmp;														\
	size_t expected_size = 0;										\
	int inc = (LAST - FIRST) >> sizeof(int) | 0x1;					\
	for (size_t i=FIRST;(int)i-LAST != inc;i += inc) {				\
		size_t added_size = snprintf(NULL, 0, "%zu\t%zu\n",i,i);	\
		expected = realloc(expected, expected_size+added_size+1);	\
		tmp = expected + expected_size;								\
		expected_size += added_size;								\
		sprintf(tmp, "%zu\t%zu\n", i, i); }							\
	cr_redirect_stdout();											\
	CALL_HISTORY(__VA_ARGS__);										\
	FILE *got = cr_get_redirected_stdout();							\
	cr_assert_file_contents_eq_str(got, expected);					\
	}

#define CHECK_WITH_RANGE(FIRST, LAST, ...) QUICK_CHECK_WITH_RANGE(10, 10, FIRST, LAST, __VA_ARGS__)

Test(builtin_history, 3_cmds_for_10_spots) {
	QUICK_CHECK_WITH_RANGE(10, 3, 1, 3, ); }

Test(builtin_history, 10_cmds_for_10_spots) {
	QUICK_CHECK_WITH_RANGE(10, 3, 1, 10, ); }

Test(builtin_history, 12_cmds_for_10_spots) {
	QUICK_CHECK_WITH_RANGE(10, 12, 3, 12, ); }

Test(builtin_history, 12_cmds_for_1_spot) {
	QUICK_CHECK_WITH_RANGE(1, 12, 12, 12, ); }

Test(builtin_history, 10_cmds_list_1_to_3) {
	CHECK_WITH_RANGE(1, 3, "1", "3", ); }

Test(builtin_history, 10_cmds_list_3_to_7) {
	CHECK_WITH_RANGE(3, 7, "3", "7", ); }

Test(builtin_history, 10_cmds_list_7_to_10) {
	CHECK_WITH_RANGE(7, 10, "7", "10", ); }

Test(builtin_history, 10_cmds_list_0_to_1000) {
	CHECK_WITH_RANGE(1, 10, "0", "1000", ); }

Test(builtin_history, 10_cmds_list_100_to_1000) {
	CHECK_WITH_RANGE(10, 10, "100", "1000", ); }

Test(builtin_history, 10_cmds_list_0_to_0) {
	CHECK_WITH_RANGE(1, 1, "0", "0", ); }

Test(builtin_history, 10_cmds_list_3_to_3) {
	CHECK_WITH_RANGE(3, 3, "3", "3", ); }

Test(builtin_history, 10_cmds_list_10_to_1) {
	CHECK_WITH_RANGE(10, 1, "10", "1", ); }

Test(builtin_history, 10_cmds_list_4_to_3) {
	CHECK_WITH_RANGE(4, 3, "4", "3", ); }

Test(builtin_history, 10_cmds_list_5_to_3) {
	CHECK_WITH_RANGE(5, 3, "5", "3", ); }

Test(builtin_history, 10_cmds_list_100_to_0) {
	CHECK_WITH_RANGE(10, 1, "100", "0", ); }

Test(builtin_history, 10_cmds_list_1_to_n1) {
	CHECK_WITH_RANGE(1, 10, "1", "-1", ); }

Test(builtin_history, 10_cmds_list_3_to_n1) {
	CHECK_WITH_RANGE(3, 10, "3", "-1", ); }

Test(builtin_history, 10_cmds_list_3_to_n5) {
	CHECK_WITH_RANGE(3, 6, "3", "-5", ); }

Test(builtin_history, 10_cmds_list_10_to_n5) {
	CHECK_WITH_RANGE(10, 6, "10", "-5", ); }

Test(builtin_history, 10_cmds_list_n10_to_n1) {
	CHECK_WITH_RANGE(1, 10, "--", "-10", "-1", ); }

Test(builtin_history, 10_cmds_list_n1_to_n10) {
	CHECK_WITH_RANGE(10, 1, "--", "-1", "-10", ); }

Test(builtin_history, 10_cmds_list_n100_to_n5) {
	CHECK_WITH_RANGE(1, 6, "--", "-100", "-5", ); }

Test(builtin_history, 10_cmds_list_100_to_n100) {
	CHECK_WITH_RANGE(10, 1, "100", "-100", ); }

Test(builtin_history, 10_cmds_list_1_to_n10_in_reverse) {
	CHECK_WITH_RANGE(10, 1, "-r", "1", "10", ); }

Test(builtin_history, 10_cmds_list_n1_to_n5_in_reverse) {
	CHECK_WITH_RANGE(6, 10, "-r", "--", "-1", "-5", ); }

Test(builtin_history, 10_cmds_list_p1_to_p3) {
	CHECK_WITH_RANGE(1, 3, "+1", "+3", ); }

Test(builtin_history, strings_as_ids) {
	POPULATE_HISTORY(3, "a", "b", "c",);
	cr_redirect_stdout();
	CALL_HISTORY("a", "c",);
	cr_assert_file_contents_eq_str(cr_get_redirected_stdout(),
								   "1\ta\n"
								   "2\tb\n"
								   "3\tc\n");}

Test(builtin_history, strings_as_ids_again) {
	POPULATE_HISTORY(10, "abc", "def", "ghi", "jkl", "mno", "pqr");
	cr_redirect_stdout();
	CALL_HISTORY("mno", "ghi",);
	cr_assert_file_contents_eq_str(cr_get_redirected_stdout(),
								   "5\tmno\n"
								   "4\tjkl\n"
								   "3\tghi\n");}

Test(builtin_history, 3_cmds_list_1_to_3_without_numbers) {
	history_init(3);
	t_string str;
	for (size_t i=1;i<=3;i++) {
		history_add(string_init_dup(&str, ft_utoa_base(i, 10)));
	}
	cr_redirect_stdout();
	CALL_HISTORY("-n", "1", "3",);
	FILE *got = cr_get_redirected_stdout();
	char *expected =
		"\t1\n"
		"\t2\n"
		"\t3\n";
	cr_assert_file_contents_eq_str(got, expected);
}

Test(builtin_history, 0_cmds_list) {
	history_init(1);
	cr_redirect_stderr();
	CALL_HISTORY();
	cr_assert_file_contents_eq_str(cr_get_redirected_stderr(), "history: no history (yet)\n");
}

Test(builtin_history, wrong_option) {
	t_string str;
	history_init(1);
	history_add(string_init_dup(&str, "test"));
	cr_redirect_stderr();
	CALL_HISTORY("-l",);
	cr_assert_file_contents_eq_str(cr_get_redirected_stderr(), "history: bad option: -l.\n");
}

Test(builtin_history, too_much_params) {
	t_string str;
	history_init(1);
	history_add(string_init_dup(&str, "test"));
	cr_redirect_stderr();
	CALL_HISTORY("test", "test", "test",);
	cr_assert_file_contents_eq_str(cr_get_redirected_stderr(), "usage: history [-nr] [first [last]].\n");
}

Test(builtin_history, str_not_in_history) {
	t_string str;
	history_init(1);
	history_add(string_init_dup(&str, "test"));
	cr_redirect_stderr();
	CALL_HISTORY("stet",);
	cr_assert_file_contents_eq_str(cr_get_redirected_stderr(), "42sh: history: not in history: stet\n");
}

Test(builtin_history, two_str_not_in_history) {
	t_string str;
	history_init(1);
	history_add(string_init_dup(&str, "test"));
	cr_redirect_stderr();
	CALL_HISTORY("stet", "tset",);
	cr_assert_file_contents_eq_str(cr_get_redirected_stderr(), "42sh: history: not in history: stet\n");
}
