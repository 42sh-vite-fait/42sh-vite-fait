#include "header.h"

static void	test_00_strchr_FirstChar(void)
{
	char	*str = "Hello World!";
	char	*ret;
	char	*valid;

	ret = ft_strchr(str, 'H');
	valid = strchr(str, 'H');
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_01_strchr_Null(void)
{
	char	*str = "Hello World!";
	char	*ret;
	char	*valid;

	ret = ft_strchr(str, 0);
	valid = strchr(str, 0);
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_02_strchr_LongStringOneChar(void)
{
	char	*str = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed "
					"eu tortor porttitor nunc porttitor aliquam. Quisque a varius lorem. "
					"Suspendisse vestibulum mi1 id urna scelerisque molestie. Proin libero "
					"justo, venenatis ac ante quis, eleifend tempus tellus. Vestibulum "
					"suscipit magna in commodo condimentum. Maecenas mattis tellus augue, ";
	char	*ret;
	char	*valid;

	ret = ft_strchr(str, '1');
	valid = strchr(str, '1');
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_03_strchr_LongStringSeveralChars(void)
{
	char	*str = "Lorem ipsum dolor sit amet, 1consectetur adipiscing elit. Sed "
					"eu tortor porttitor nunc porttitor aliquam. Quisque a varius l1orem. "
					"Suspendisse vestibulum mi1 id urna scelerisque molestie. Proin libero "
					"justo, venenatis ac a1nte quis, eleifend tempus tellus. Vestibulum "
					"suscipit magna in comm1odo condimentum. Maecenas mattis tellus augue, ";
	char	*ret;
	char	*valid;

	ret = ft_strchr(str, '1');
	valid = strchr(str, '1');
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_04_strchr_NoChar(void)
{
	char	*str = "Hello World!";
	char	*ret;
	char	*valid;

	ret = ft_strchr(str, 'z');
	valid = strchr(str, 'z');
	v_assert_ptr(valid, ==, ret);

	VTS;
}

/*
 * strchrpos
 */
static void	test_00_strchrpos_SimpleString1(void)
{
	int ret;

	ret = ft_strchrpos("Hello World!", 'H');
	v_assert_int(0, ==, ret);

	VTS;
}

static void	test_01_strchrpos_SimpleString2(void)
{
	int ret;

	ret = ft_strchrpos("Hello World!", '!');
	v_assert_int(11, ==, ret);

	VTS;
}

static void	test_02_strchrpos_CharNotFound(void)
{
	int ret;

	ret = ft_strchrpos("Hello World!", '#');
	v_assert_int(-1, ==, ret);

	VTS;
}

static void	test_03_strchrpos_TwoOccurrence(void)
{
	int ret;

	ret = ft_strchrpos("Hello World!", 'o');
	v_assert_int(4, ==, ret);

	VTS;
}

static void	test_04_strchrpos_EndOfString(void)
{
	int ret;

	ret = ft_strchrpos("Hello World!", 0);
	v_assert_int(12, ==, ret);

	VTS;
}

/*
 * strchr
 */
static void	test_00_strnchr_MaxOfOne(void)
{
	char	*str = "Hello World!";
	char	*ret;

	ret = ft_strnchr(str,'H', 1);
	v_assert_str(str, ret);

	VTS;
}

static void	test_01_strnchr_EndOfString(void)
{
	char	*str = "Hello World!";
	char	*ret;

	ret = ft_strnchr(str, '\0', 20);
	v_assert_str("", ret);

	VTS;
}

static void	test_02_strnchr_NotEnoughLen(void)
{
	char	*str = "Hello World!";
	char	*ret;

	ret = ft_strnchr(str, 'W', 6);
	v_assert_ptr(NULL, ==, ret);

	VTS;
}

void		suite_strchr(void)
{
	test_00_strchr_FirstChar();
	test_01_strchr_Null();
	test_02_strchr_LongStringOneChar();
	test_03_strchr_LongStringSeveralChars();
	test_04_strchr_NoChar();

	test_00_strchrpos_SimpleString1();
	test_01_strchrpos_SimpleString2();
	test_02_strchrpos_CharNotFound();
	test_03_strchrpos_TwoOccurrence();
	test_04_strchrpos_EndOfString();

	test_00_strnchr_MaxOfOne();
	test_01_strnchr_EndOfString();
	test_02_strnchr_NotEnoughLen();

	VSS;
}
