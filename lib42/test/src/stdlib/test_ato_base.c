#include "header.h"

#define TEST_UBASE(s, e, b)				\
	do									\
	{									\
		size_t ret = ft_atou_base(s, b);\
		v_assert_size_t((e), ==, ret);	\
	} while (0);						\

#define TEST_IBASE(s, e, b)					\
	do										\
	{										\
		ssize_t ret = ft_atoi_base(s, b);	\
		v_assert_long((e), ==, ret);		\
	} while (0);							\

#define TEST_U(s, e)					\
	do									\
	{									\
		size_t ret = ft_atou(s);		\
		v_assert_size_t((e), ==, ret);	\
	} while (0);						\

static void	test_atou_ExceedBase(void)
{
	TEST_UBASE("ab", 10, 11);

	VTS;
}

static void	test_ato_Binary(void)
{
	TEST_UBASE("0", 0, 0x2);
	TEST_UBASE("1", 1, 0x2);
	TEST_UBASE("10", 2, 0x2);
	TEST_UBASE("1111111111111111111111111111111111111111111111111111111111111111", UINT64_MAX, 0x2);
	TEST_IBASE("111111111111111111111111111111111111111111111111111111111111111", INT64_MAX, 0x2);
	TEST_IBASE("-1000000000000000000000000000000000000000000000000000000000000000", INT64_MIN, 0x2);
	TEST_U("0b10", 2);

	VTS;
}

static void	test_ato_Octal(void)
{
	TEST_UBASE("7", 7, 0x8);
	TEST_UBASE("10", 8, 0x8);
	TEST_IBASE("-10", -8, 0x8);
	TEST_UBASE("1777777777777777777777", UINT64_MAX, 0x8);
	TEST_IBASE("777777777777777777777", INT64_MAX, 0x8);
	TEST_IBASE("1000000000000000000000", INT64_MIN, 0x8);

	VTS;
}

static void	test_ato_Decimal(void)
{
	TEST_UBASE("666", 666, 0xA);
	TEST_IBASE("-9223372036854775808", INT64_MIN, 0xA);
	TEST_IBASE("9223372036854775807", INT64_MAX, 0xA);
	TEST_UBASE("18446744073709551615", UINT64_MAX, 0xA);
	TEST_UBASE("100", 256, 0x10);
	TEST_UBASE("A", 10, 0x10);
	TEST_IBASE("-8000000000000000", INT64_MIN, 0x10);
	TEST_IBASE("7FFFFFFFFFFFFFFF", INT64_MAX, 0x10);
	TEST_UBASE("FFFFFFFFFFFFFFFF", UINT64_MAX, 0x10);

	VTS;
}

static void	test_atou_StopBeforeNulEnding(void)
{
	TEST_U("123lol", 123);
	TEST_IBASE("-1-23lol", -1, 10);

	VTS;
}

static void	test_atou_PrefixString(void)
{
	TEST_U("0100", 64);
	TEST_U("0b100", 4);
	TEST_U("0x100", 256);

	VTS;
}

void	suite_ato_base(void)
{
	test_ato_Binary();
	test_ato_Octal();
	test_ato_Decimal();

	test_atou_ExceedBase();
	test_atou_StopBeforeNulEnding();
	test_atou_PrefixString();

	VSS;
}
