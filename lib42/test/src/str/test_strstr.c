#include "header.h"

static void	test_00_strstr_SecondWorld(void)
{
	char	*big = "Hello World!";
	char	*little = "World";
	char	*ret;
	char	*valid;

	ret = ft_strstr(big, little);
	valid = strstr(big, little);
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_01_strstr_Null(void)
{
	char	*big = "Hello World!";
	char	*little = "\0";
	char	*ret;
	char	*valid;

	ret = ft_strstr(big, little);
	valid = strstr(big, little);
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_02_strstr_LongStringOneChar(void)
{
	char	*big = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed "
					"eu tortor porttitor nunc porttitor aliquam. Quisque a varius lorem. "
					"Suspendisse vestibulum mi1 id urna scelerisque molestie. Proin libero "
					"justo, venenatis ac ante quis, eleifend tempus tellus. Vestibulum "
					"suscipit magna in commodo condimentum. Maecenas mattis tellus augue, ";
	char	*little = "1";
	char	*ret;
	char	*valid;

	ret = ft_strstr(big, little);
	valid = strstr(big, little);
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_03_strstr_LongStringSeveralChars(void)
{
	char	*big = "Lorem ipsum dolor sit amet, 1consectetur adipiscing elit. Sed "
					"eu tortor porttitor nunc porttitor aliquam. Quisque a varius l1orem. "
					"Suspendisse vestibulum mi1 id urna scelerisque molestie. Proin libero "
					"justo, venenatis ac a1nte quis, eleifend tempus tellus. Vestibulum "
					"suscipit magna in comm1odo condimentum. Maecenas mattis tellus augue, ";
	char	*little = "1";
	char	*ret;
	char	*valid;

	ret = ft_strstr(big, little);
	valid = strstr(big, little);
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_04_strstr_NoChar(void)
{
	char	*big = "Hello World!";
	char	*little = "1";
	char	*ret;
	char	*valid;

	ret = ft_strstr(big, little);
	valid = strstr(big, little);
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_05_strstr_LittleBiggerThanBig(void)
{
	char	*big = "Hello World!";
	char	*little = "Hello Matrix World!";
	char	*ret;
	char	*valid;

	ret = ft_strstr(big, little);
	valid = strstr(big, little);
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_06_strstr_LittleEqualBig(void)
{
	char	*big = "Hello World!";
	char	*little = "Hello World!";
	char	*ret;
	char	*valid;

	ret = ft_strstr(big, little);
	valid = strstr(big, little);
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_07_strstr_AlmostEqual(void)
{
	char	*big = "Hello World!";
	char	*little = "Hello World ";
	char	*ret;
	char	*valid;

	ret = ft_strstr(big, little);
	valid = strstr(big, little);
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_08_strstr_ResultAtEnd(void)
{
	char	*big = "Hello World!";
	char	*little = "!";
	char	*ret;
	char	*valid;

	ret = ft_strstr(big, little);
	valid = strstr(big, little);
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_09_strstr_StrangeInfiniteLoop(void)
{
	char	*big = "potos\n";
	char	*little = "\\\n";
	char	*ret;
	char	*valid;

	ret = ft_strstr(big, little);
	valid = strstr(big, little);
	v_assert_ptr(valid, ==, ret);

	VTS;
}

void		suite_strstr(void)
{
	test_00_strstr_SecondWorld();
	test_01_strstr_Null();
	test_02_strstr_LongStringOneChar();
	test_03_strstr_LongStringSeveralChars();
	test_04_strstr_NoChar();
	test_05_strstr_LittleBiggerThanBig();
	test_06_strstr_LittleEqualBig();
	test_07_strstr_AlmostEqual();
	test_08_strstr_ResultAtEnd();

	test_09_strstr_StrangeInfiniteLoop();

	VSS;
}
