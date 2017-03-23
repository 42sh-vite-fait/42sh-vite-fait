#include "header.h"

static void	test_00_next_power_of_2_NotAPowerOf2(void)
{
	size_t	ret;

	ret = next_power_of_2(7);
	v_assert_size_t(8, ==, ret);

	ret = next_power_of_2(51);
	v_assert_size_t(64, ==, ret);

	ret = next_power_of_2(1234);
	v_assert_size_t(2048, ==, ret);

	VTS;
}

static void	test_01_next_power_of_2_APowerOf2(void)
{
	size_t	ret;

	ret = next_power_of_2(8);
	v_assert_size_t(16, ==, ret);

	ret = next_power_of_2(128);
	v_assert_size_t(256, ==, ret);

	VTS;
}

static void	test_02_next_power_of_2_Zero(void)
{
	size_t	ret;

	ret = next_power_of_2(0);
	v_assert_size_t(1, ==, ret);

	VTS;
}

void	suite_next_power_of_2(void)
{
	test_00_next_power_of_2_NotAPowerOf2();
	test_01_next_power_of_2_APowerOf2();
	test_02_next_power_of_2_Zero();

	VSS;
}
