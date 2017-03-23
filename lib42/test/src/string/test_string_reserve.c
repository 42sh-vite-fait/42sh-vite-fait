#include "header.h"

static t_string		string;

static void	teardown(void)
{
	free(string.str);
}

static void	test_00_string_reserve_DontNeedExpansion(void)
{
	string_init_with_capacity(&string, 4);
	v_assert_size_t(STRING_INIT_SIZE, ==, string.capacity);

	string_reserve(&string, 7);
	v_assert_size_t(STRING_INIT_SIZE, ==, string.capacity);

	teardown();
	VTS;
}

static void	test_01_string_reserve_ExpandMoreThan2(void)
{
	string_init_with_capacity(&string, 1111);
	v_assert_size_t(2048, ==, string.capacity);

	string_reserve(&string, 5555);
	v_assert_size_t(8192, ==, string.capacity);

	teardown();
	VTS;
}

static void	test_02_string_reserve_ExpandUseless(void)
{
	string_init_with_capacity(&string, 256); // '\0' make it be 257
	v_assert_size_t(512, ==, string.capacity);

	// len is 0 then it doesn't need to realloc
	string_reserve(&string, 256); // 0 + 256 = 256 -> 512
	v_assert_size_t(512, ==, string.capacity);

	teardown();
	VTS;
}

static void	test_03_string_reserve_ExpandPowerOf2(void)
{
	char		*big_str;

	string_init_with_capacity(&string, 255);
	v_assert_size_t(256, ==, string.capacity);

	big_str = ft_memalloc(257); // '\0' everywhere
	ft_memset(big_str, 'c', 256);

	string_ncat(&string, big_str, 256); // 0 + (256 + 1) = 257 -> 1024
	v_assert_size_t(512, ==, string.capacity);

	teardown();
	free(big_str);
	VTS;
}

static void	test_03_string_reserve_ExpandFor2Strings(void)
{
	char		*first_str;
	char		*second_str;

	first_str = ft_memalloc(256); // '\0' everywhere
	ft_memset(first_str, 'a', 255);

	string_init_ndup(&string, first_str, 255);
	v_assert_size_t(256, ==, string.capacity);

	second_str = ft_memalloc(258); // '\0' everywhere
	ft_memset(second_str, 'b', 257);

	string_ncat(&string, second_str, 257); // 255 + (257 + 1) = 513 -> 1024
	v_assert_size_t(1024, ==, string.capacity);

	free(first_str);
	free(second_str);
	teardown();
	VTS;
}

void	suite_string_reserve(void)
{
	test_00_string_reserve_DontNeedExpansion();
	test_01_string_reserve_ExpandMoreThan2();
	test_02_string_reserve_ExpandUseless();
	test_03_string_reserve_ExpandPowerOf2();
	test_03_string_reserve_ExpandFor2Strings();

	VSS;
}
