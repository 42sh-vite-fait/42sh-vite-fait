#include "header.h"

static void	test_00_strrchr_FirstChar(void)
{
	char	*str = "Hello World!";
	char	*ret;
	char	*valid;

	ret = ft_strrchr(str, 'H');
	valid = strrchr(str, 'H');
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_01_strrchr_Null(void)
{
	char	*str = "Hello World!";
	char	*ret;
	char	*valid;

	ret = ft_strrchr(str, 0);
	valid = strrchr(str, 0);
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_02_strrchr_LongStringOneChar(void)
{
	char	*str = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed "
					"eu tortor porttitor nunc porttitor aliquam. Quisque a varius lorem. "
					"Suspendisse vestibulum mi1 id urna scelerisque molestie. Proin libero "
					"justo, venenatis ac ante quis, eleifend tempus tellus. Vestibulum "
					"suscipit magna in commodo condimentum. Maecenas mattis tellus augue, ";
	char	*ret;
	char	*valid;

	ret = ft_strrchr(str, '1');
	valid = strrchr(str, '1');
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_03_strrchr_LongStringSeveralChars(void)
{
	char	*str = "Lorem ipsum dolor sit amet, 1consectetur adipiscing elit. Sed "
					"eu tortor porttitor nunc porttitor aliquam. Quisque a varius l1orem. "
					"Suspendisse vestibulum mi1 id urna scelerisque molestie. Proin libero "
					"justo, venenatis ac a1nte quis, eleifend tempus tellus. Vestibulum "
					"suscipit magna in comm1odo condimentum. Maecenas mattis tellus augue, ";
	char	*ret;
	char	*valid;

	ret = ft_strrchr(str, '1');
	valid = strrchr(str, '1');
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_04_strrchr_NoChar(void)
{
	char	*str = "Hello World!";
	char	*ret;
	char	*valid;

	ret = ft_strrchr(str, 'z');
	valid = strrchr(str, 'z');
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void test_05_strrchr_PastStart(void)
{
	char	*str = "Hello World!";
	char	*ret;
	char	*valid;

	ret = ft_strrchr(str + 1, 'H');
	valid = strrchr(str + 1, 'H');
	v_assert_ptr(valid, ==, ret);
	v_assert_ptr(NULL, ==, ret);
	
	VTS;
}

static void test_06_strrchr_EmptyString(void)
{
	char	*str = "";
	char	*ret;
	char	*valid;

	ret = ft_strrchr(str, '\0');
	valid = strrchr(str, '\0');
	v_assert_ptr(valid, ==, ret);
	v_assert_ptr(str, ==, ret);
	
	VTS;
}

/*
 * ft_strrchrpos
 */
static void	test_00_strrchrpos_SimpleString1(void)
{
	int ret;

	ret = ft_strrchrpos("Hello World!", 'H');
	v_assert_int(0, ==, ret);

	VTS;
}

static void	test_01_strrchrpos_SimpleString2(void)
{
	int ret;

	ret = ft_strrchrpos("Hello World!", '!');
	v_assert_int(11, ==, ret);

	VTS;
}

static void	test_02_strrchrpos_CharNotFound(void)
{
	int ret;

	ret = ft_strrchrpos("Hello World!", '#');
	v_assert_int(-1, ==, ret);

	VTS;
}

static void	test_03_strrchrpos_TwoOccurrence(void)
{
	int ret;

	ret = ft_strrchrpos("Hello World!", 'o');
	v_assert_int(7, ==, ret);

	VTS;
}

static void	test_04_strrchrpos_EndOfString(void)
{
	int ret;

	ret = ft_strrchrpos("Hello World!", 0);
	v_assert_int(12, ==, ret);

	VTS;
}

static void	test_05_strrchrpos_SimpleString3(void)
{
	int ret;

	ret = ft_strrchrpos("Hello World!", 'd');
	v_assert_int(10, ==, ret);

	VTS;
}

/*
 * ft_strrnchrpos
 */
static void	test_00_strrnchr_LimitChar(void)
{
	char	*str = "Hello World!";
	char	*ret;

	ret = ft_strrnchr(str, 'o', 6);
	v_assert_str("orld!", ret);

	VTS;
}

static void	test_01_strrnchr_Null(void)
{
	char	*str = "Hello World!";
	char	*ret;

	ret = ft_strrnchr(str, '\0', 1);
	v_assert_str("", ret);

	VTS;
}

static void	test_02_strrnchr_PastLimitChar(void)
{
	char	*str = "Hello World!";
	char	*ret;

	ret = ft_strrnchr(str, 'o', 4);
	v_assert_ptr(NULL, ==, ret);

	VTS;
}

static void test_03_strrnchr_EmptyStringNullSize(void)
{
	char	*str = "";
	char	*ret;

	ret = ft_strrnchr(str, '\0', 0);
	v_assert_ptr(NULL, ==, ret);
	
	VTS;
}

void	suite_strrchr(void)
{
	test_00_strrchr_FirstChar();
	test_01_strrchr_Null();
	test_02_strrchr_LongStringOneChar();
	test_03_strrchr_LongStringSeveralChars();
	test_04_strrchr_NoChar();
	test_05_strrchr_PastStart();
	test_06_strrchr_EmptyString();

	test_00_strrchrpos_SimpleString1();
	test_01_strrchrpos_SimpleString2();
	test_02_strrchrpos_CharNotFound();
	test_03_strrchrpos_TwoOccurrence();
	test_04_strrchrpos_EndOfString();
	test_05_strrchrpos_SimpleString3();

	test_00_strrnchr_LimitChar();
	test_01_strrnchr_Null();
	test_02_strrnchr_PastLimitChar();
	test_03_strrnchr_EmptyStringNullSize();

	VSS;
}
