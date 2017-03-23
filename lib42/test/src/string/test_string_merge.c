#include "header.h"

static void	test_00_string_merge_NoRealloc(void)
{
	t_string	b1;
	t_string	b2;
	t_string	merge;
	char		*s1 = "Hello World!";
	char		*s2 = "Good Morning";
	char		s[100];
	size_t		l1 = strlen(s1);
	size_t		l2 = strlen(s2);

	s[0] = '\0';
	strcat(s, s1);
	strcat(s, s2);
	string_init_dup(&b1, s1);
	string_init_dup(&b2, s2);
	string_merge(&merge, &b1, &b2);

	v_assert_str(s1, b1.str);
	v_assert_str(s2, b2.str);
	v_assert_size_t(STRING_INIT_SIZE, ==, merge.capacity);
	v_assert_size_t(l1 + l2, ==, merge.len);
	v_assert_str(s, merge.str);

	free(b1.str);
	free(b2.str);
	free(merge.str);
	VTS;
}

static void	test_01_string_merge_Realloc(void)
{
	t_string	b1;
	t_string	b2;
	t_string	merge;
	char		s1[100];
	char		s2[100];

	// setup
	memset(s1, '\0', 100);
	memset(s1, '*', STRING_INIT_SIZE + 10);
	memset(s2, '\0', 100);
	memset(s2, '#', 6);
	string_init_dup(&b1, s1);
	string_init_dup(&b2, s2);
	strcat(s1, s2);
	string_merge(&merge, &b1, &b2);

	// test
	v_assert_size_t(next_power_of_2(STRING_INIT_SIZE), ==, b1.capacity);
	v_assert_size_t(STRING_INIT_SIZE, ==, b2.capacity);
	v_assert_size_t(next_power_of_2(STRING_INIT_SIZE), ==, merge.capacity);
	v_assert_size_t(80, ==, merge.len);
	v_assert_str(s1, merge.str);

	// teardown
	free(b1.str);
	free(b2.str);
	free(merge.str);
	VTS;
}

void	suite_string_merge(void)
{
	test_00_string_merge_NoRealloc();
	test_01_string_merge_Realloc();

	VSS;
}
