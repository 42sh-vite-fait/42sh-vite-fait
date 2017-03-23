#include "header.h"

/*
** [http://wims.unice.fr/wims/fr_tool~number~baseconv.fr.html]
*/

void	test_stoa_base_2(void)
{
	char	*str;
	int		number[] = { 23, 21474, INT32_MAX, INT32_MIN };
	int		base = 2;
	char	*expected[] = { "10111",
		"101001111100010",
		"1111111111111111111111111111111",
		"-10000000000000000000000000000000" };
	size_t	len = sizeof(expected) / sizeof(expected[0]);

	for (size_t i = 0; i < len; ++i)
	{
		str = ft_stoa_base(number[i], base);
		v_assert_str(expected[i], str);
		FREE(str);
	}

	v_test_success("stoa_base_2");
}

void	test_stoa_base_8(void)
{
	char	*str;
	int		number[] = { 4444 };
	int		base = 8;
	char	*expected[] = { "10534" };
	size_t	len = sizeof(expected) / sizeof(expected[0]);

	for (size_t i = 0; i < len; ++i)
	{
		str = ft_stoa_base(number[i], base);
		v_assert_str(expected[i], str);
		FREE(str);
	}

	v_test_success("stoa_base_8");
}

void	test_stoa_base_10(void)
{
	char	*str;
	int		number[] = { INT32_MAX, INT32_MIN, 0, -0 };
	int		base = 10;
	char	*expected[] = { "2147483647", "-2147483648", "0" };
	size_t	len = sizeof(expected) / sizeof(expected[0]);

	for (size_t i = 0; i < len; ++i)
	{
		str = ft_stoa_base(number[i], base);
		v_assert_str(expected[i], str);
		FREE(str);
	}

	v_test_success("stoa_base_10");
}

void	test_stoa_base_16(void)
{
	char	*str;
	int		number[] = { INT32_MIN, INT32_MAX, 255 };
	int		base = 16;
	char	*expected[] = { "-80000000", "7fffffff", "ff" };
	size_t	len = sizeof(expected) / sizeof(expected[0]);

	for (size_t i = 0; i < len; ++i)
	{
		str = ft_stoa_base(number[i], base);
		v_assert_str(expected[i], str);
		FREE(str);
	}

	v_test_success("stoa_base_16");
}

void	suite_toa_base()
{
	test_stoa_base_2();
	test_stoa_base_8();
	test_stoa_base_10();
	test_stoa_base_16();
	v_suite_success("stoa_base");
}
