#include "header.h"
#include "criterion/criterion.h"
#include "criterion/redirect.h"

#define TRUE 1
#define FALSE 0

void	setup(void) {
	cr_redirect_stdout();
	cr_redirect_stderr();
}

TestSuite(autocompletion, .init = setup);

#define CHECK_AUTOCOMPLETE(MATCHES, STR, SHALL_BE_FOUND, CMD) {			\
	cr_assert((MATCHES.len > 0) == SHALL_BE_FOUND);						\
	for (size_t i=0;i<MATCHES.len;i++){									\
		char * m = *(char **)array_get_at(&MATCHES, i);					\
		cr_assert_str_geq(m, STR);										\
		t_string test;													\
		string_init_dup(&test, CMD);									\
		string_cat(&test, m);											\
		cr_assert(system(test.str) == 0);								\
	}																	\
}

#define COMPLETE_PATH(STR, SHALL_BE_FOUND) {							\
	t_array matches;													\
	array_init(&matches, sizeof(char *));								\
	complete_path(&matches, STR);										\
	CHECK_AUTOCOMPLETE(matches, STR, SHALL_BE_FOUND, "type ");			\
	array_shutdown(&matches);											\
}

#define COMPLETE_IN_PWD(STR, PWD, SHALL_BE_FOUND) {						\
	t_array matches;													\
	array_init(&matches, sizeof(char *));								\
	complete_cmd_in_pwd(&matches, STR, PWD);							\
	CHECK_AUTOCOMPLETE(matches, STR, SHALL_BE_FOUND, "cd "PWD";type "); \
	array_shutdown(&matches);											\
}

#define COMPLETE_IN_PATHS(STR, PATHS, SHALL_BE_FOUND) {					\
	t_array matches;													\
	array_init(&matches, sizeof(char *));								\
	complete_cmd_in_paths(&matches, STR, PATHS);						\
	CHECK_AUTOCOMPLETE(matches, STR, SHALL_BE_FOUND, "type ");			\
	array_shutdown(&matches);											\
}

Test(autocompletion, in_path_ls) {
	COMPLETE_PATH("/bin/ls", TRUE); }

Test(autocompletion, in_path_gre) {
	COMPLETE_PATH("/usr/bin/gre", TRUE); }

Test(autocompletion, in_path_coincoin) {
	COMPLETE_PATH("/usr/bin/coincoin", FALSE); }



Test(autocompletion, in_pwd_ls) {
	COMPLETE_IN_PWD("ls", "/bin", TRUE); }

Test(autocompletion, in_pwd_gre) {
	COMPLETE_IN_PWD("gre", "/usr/bin", TRUE); }

Test(autocompletion, in_pwd_coincoin) {
	COMPLETE_IN_PWD("coincoin", "/bin", FALSE); }


Test(autocompletion, in_paths_l) {
	COMPLETE_IN_PATHS("ls", getenv("PATH"), TRUE); }

Test(autocompletion, in_paths_coincoin) {
	COMPLETE_IN_PATHS("coincoin", getenv("PATH"), FALSE); }
