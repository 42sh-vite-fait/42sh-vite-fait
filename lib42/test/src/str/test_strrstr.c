#include "header.h"

static void	test_00_strrstr_SecondWorld(void)
{
	char	*big = "Hello World!";
	char	*little = "World";
	char	*ret;
	char	*valid;

	ret = ft_strrstr(big, little);
	valid = strstr(big, little);
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_01_strrstr_Null(void)
{
	char	*big = "Hello World!";
	char	*little = "";
	char	*ret;
	char	*valid;

	ret = ft_strrstr(big, little);
	valid = big + strlen(big);
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_02_strrstr_LongStringOneChar(void)
{
	char	*big = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed "
					"eu tortor porttitor nunc porttitor aliquam. Quisque a varius lorem. "
					"Suspendisse vestibulum mi1 id urna scelerisque molestie. Proin libero "
					"justo, venenatis ac ante quis, eleifend tempus tellus. Vestibulum "
					"suscipit magna in commodo condimentum. Maecenas mattis tellus augue, ";
	char	*little = "1";
	char	*ret;
	char	*valid;

	ret = ft_strrstr(big, little);
	valid = strstr(big, little);
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_03_strrstr_LongStringSeveralChars(void)
{
	char	*big = "Lorem ipsum dolor sit amet, 1consectetur adipiscing elit. Sed "
					"eu tortor porttitor nunc porttitor aliquam. Quisque a varius l1orem. "
					"Suspendisse vestibulum mi1 id urna scelerisque molestie. Proin libero "
					"justo, venenatis ac a1nte quis, eleifend tempus tellus. Vestibulum "
					"suscipit magna in comm1odo condimentum. Maecenas mattis tellus augue, ";
	char	*little = "1";
	char	*ret;
	char	*valid;

	ret = ft_strrstr(big, little);
	valid = big + 290;
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_04_strrstr_NoChar(void)
{
	char	*big = "Hello World!";
	char	*little = "1";
	char	*ret;
	char	*valid;

	ret = ft_strrstr(big, little);
	valid = strstr(big, little);
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_05_strrstr_LittleBiggerThanBig(void)
{
	char	*big = "Hello World!";
	char	*little = "Hello Matrix World!";
	char	*ret;
	char	*valid;

	ret = ft_strrstr(big, little);
	valid = strstr(big, little);
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_06_strrstr_LittleEqualBig(void)
{
	char	*big = "Hello World!";
	char	*little = "Hello World!";
	char	*ret;
	char	*valid;

	ret = ft_strrstr(big, little);
	valid = strstr(big, little);
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_07_strrstr_AlmostEqual(void)
{
	char	*big = "Hello World!";
	char	*little = "Hello World ";
	char	*ret;
	char	*valid;

	printf("start\n");
	ret = ft_strrstr(big, little);
	valid = strstr(big, little);
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_08_strrstr_ResultAtEnd(void)
{
	char	*big = "Hello World!";
	char	*little = "!";
	char	*ret;
	char	*valid;

	ret = ft_strrstr(big, little);
	valid = strstr(big, little);
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_09_strrstr_DoesntMatch(void)
{
	char	*big = "ls -la";
	char	*little = "kiki";
	char	*ret;
	char	*valid;

	ret = ft_strrstr(big, little);
	valid = strstr(big, little);
	v_assert_ptr(valid, ==, ret);

	VTS;
}

static void	test_10_strrstr_MultipleCharWichFollow(void)
{
	char	*big = strdup("echo llllllllll");
	char	*little = "l";
	char	*ret;
	char	*valid;

	v_assert_ptr(big + 14, ==, ft_strrstr(big, little));
	big[14] = '\0';
	v_assert_ptr(big + 13, ==, ft_strrstr(big, little));
	big[13] = '\0';
	v_assert_ptr(big + 12, ==, ft_strrstr(big, little));
	big[12] = '\0';
	v_assert_ptr(big + 11, ==, ft_strrstr(big, little));

	free(big);
	VTS;
}

static void	test_11_strrstr_MultipleCharWichFollowLittlePattern(void)
{
	char	*big = strdup("echo llllllllll");
	char	*little = "ll";
	char	*ret;
	char	*valid;

	v_assert_ptr(big + 13, ==, ft_strrstr(big, little));
	big[14] = '\0';
	v_assert_ptr(big + 12, ==, ft_strrstr(big, little));
	big[13] = '\0';
	v_assert_ptr(big + 11, ==, ft_strrstr(big, little));
	big[12] = '\0';
	v_assert_ptr(big + 10, ==, ft_strrstr(big, little));

	free(big);
	VTS;
}

static void	test_12_strrstr_GrowingPattern(void)
{
	char	*big = strdup("qqqqqqqqq");

	v_assert_ptr(big + 8, ==, ft_strrstr(big, "q"));
	v_assert_ptr(big + 7, ==, ft_strrstr(big, "qq"));
	v_assert_ptr(big + 6, ==, ft_strrstr(big, "qqq"));
	v_assert_ptr(big + 5, ==, ft_strrstr(big, "qqqq"));

	free(big);
	VTS;
}

static void	test_13_strrstr_StrangeTextAndPattern(void)
{
	const char *big = "qqqqw";

	v_assert_ptr(big, ==, ft_strrstr(big, "qqqq"));
	VTS;
}

void		suite_strrstr(void)
{
	test_00_strrstr_SecondWorld();
	test_01_strrstr_Null();
	test_02_strrstr_LongStringOneChar();
	test_03_strrstr_LongStringSeveralChars();
	test_04_strrstr_NoChar();
	test_05_strrstr_LittleBiggerThanBig();
	test_06_strrstr_LittleEqualBig();
	test_07_strrstr_AlmostEqual();
	test_08_strrstr_ResultAtEnd();
	test_09_strrstr_DoesntMatch();
	test_10_strrstr_MultipleCharWichFollow();
	test_11_strrstr_MultipleCharWichFollowLittlePattern();
	test_12_strrstr_GrowingPattern();
	test_13_strrstr_StrangeTextAndPattern();

	VSS;
}
