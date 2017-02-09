#include "header.h"
#include "criterion/criterion.h"

TestSuite(PathScanning);

#define TEST(...) {										\
	t_string p;											\
	size_t i = 0;										\
	const char *args[] = {__VA_ARGS__};					\
	const char *path = args[0];							\
	const char **expected = args + 1;					\
	size_t expected_len = sizeof(args)/sizeof(*args)-1;	\
	string_init(&p);									\
	while ((path = get_next_path(&p, path)) != NULL) {	\
		cr_assert_str_eq(p.str, expected[i]);			\
		i +=1;											\
	}													\
	cr_assert(i == expected_len);						\
	string_shutdown(&p);								\
	}

Test(PathScanning, Simple) {
	TEST("/bin/:/sbin/:/usr/bin/",
		 "/bin/", "/sbin/", "/usr/bin/"); }

Test(PathScanning, SimpleWithoutFinalSlashes) {
	TEST("/bin:/usr:/sbin/",
		 "/bin/", "/usr/", "/sbin/"); }

Test(PathScanning, Empty) {
	TEST(""); }

Test(PathScanning, EmptyPathInPaths) {
	TEST("/bin::/usr",
		 "/bin/", "./", "/usr/"); }

Test(PathScanning, EmptyPathsInPaths) {
	TEST("/bin/:::/usr::::/sbin",
		 "/bin/", "./", "./", "/usr/", "./", "./", "./", "/sbin/"); }

Test(PathScanning, EmptyPathInPathsStart) {
	TEST(":/bin/",
		 "./", "/bin/"); }

Test(PathScanning, EmptyPathInPathsEnd) {
	TEST("/bin:",
		 "/bin/", "./"); }

Test(PathScanning, JustAnEmptyPath) {
	TEST(":",
		"./"); }

Test(PathScanning, SomeEmptyPaths) {
	TEST(":::",
		 "./", "./", "./"); }

Test(PathScanning, IncorrectPath) {
	TEST("/incorrect_path"); }

Test(PathScanning, IncorrectPathInPaths) {
	TEST("/bin:/incorrect_path:/usr/bin",
		 "/bin/", "/usr/bin/"); }

Test(PathScanning, OnePathToRuleThemAll)
{
	TEST("/var", "/var/");
}

Test(PathScanning, OnePathToRuleThemAllWithSlash)
{
	TEST("/var/", "/var/");
}
