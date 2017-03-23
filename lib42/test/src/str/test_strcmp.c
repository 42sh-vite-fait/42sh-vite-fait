#include "header.h"

static void	test_00_strcmp_EqualString(void)
{
	char	*s1 = "Hello World!";
	char	*s2 = "Hello World!";
	int		valid;
	int		ret;

	valid = strcmp(s1, s2);
	ret = ft_strcmp(s1, s2);

	v_assert_int(valid, ==, ret);

	VTS;
}

static void	test_01_strcmp_UnequalString(void)
{
	char	*s1 = "Hello World!";
	char	*s2 = "Hello xorld!";
	int		valid;
	int		ret;

	valid = strcmp(s1, s2);
	ret = ft_strcmp(s1, s2);

#if defined(__APPLE__)
	(void)valid;
	v_assert_int(0, !=, ret);
#else
	v_assert_int(valid, ==, ret);
#endif

	VTS;
}

static void	test_02_strcmp_EmptyString(void)
{
	char	*s1 = "";
	char	*s2 = "Hello World!";
	int		valid;
	int		ret;

	valid = strcmp(s1, s2);
	ret = ft_strcmp(s1, s2);

#if defined(__APPLE__)
	(void)valid;
	v_assert_int(0, !=, ret);
#else
	v_assert_int(valid, ==, ret);
#endif

	VTS;
}

static void	test_03_strcmp_DoubleEmptyString(void)
{
	char	*s1 = "";
	char	*s2 = "";
	int		valid;
	int		ret;

	valid = strcmp(s1, s2);
	ret = ft_strcmp(s1, s2);

	v_assert_int(valid, ==, ret);

	VTS;
}

static void	test_04_strcmp_FirstCharDifferent(void)
{
	char	*s1 = "abcdef";
	char	*s2 = "bcdef";
	int		valid;
	int		ret;

	valid = strcmp(s1, s2);
	ret = ft_strcmp(s1, s2);

#if defined(__APPLE__)
	(void)valid;
	v_assert_int(0, !=, ret);
#else
	v_assert_int(valid, ==, ret);
#endif

	VTS;
}

static void	test_05_strcmp_LastCharDifferent(void)
{
	char	*s1 = "abcdef";
	char	*s2 = "abcdeg";
	int		valid;
	int		ret;

	valid = strcmp(s1, s2);
	ret = ft_strcmp(s1, s2);

#if defined(__APPLE__)
	(void)valid;
	v_assert_int(0, !=, ret);
#else
	v_assert_int(valid, ==, ret);
#endif

	VTS;
}


// strncmp
static void	test_00_strncmp_EqualString(void)
{
	char	*s1 = "Hello World!";
	char	*s2 = "Hello World!";
	int		valid;
	int		ret;

	valid = strncmp(s1, s2, 20);
	ret = ft_strncmp(s1, s2, 20);

	v_assert_int(valid, ==, ret);

	VTS;
}

static void	test_01_strncmp_UnequalString(void)
{
	char	*s1 = "Hello World!";
	char	*s2 = "Hello xorld!";
	int		valid;
	int		ret;

	valid = strncmp(s1, s2, 20);
	ret = ft_strncmp(s1, s2, 20);

#if defined(__APPLE__)
	(void)valid;
	v_assert_int(0, !=, ret);
#else
	v_assert_int(valid, ==, ret);
#endif

	VTS;
}

static void	test_03_strncmp_UnequalStringBeforeN(void)
{
	char	*s1 = "Hello World!";
	char	*s2 = "Hello xorld!";
	int		valid;
	int		ret;

	valid = strncmp(s1, s2, 7);
	ret = ft_strncmp(s1, s2, 7);

#if defined(__APPLE__)
	(void)valid;
	v_assert_int(0, !=, ret);
#else
	v_assert_int(valid, ==, ret);
#endif

	VTS;
}

static void	test_04_strncmp_UnequalStringAfterN(void)
{
	char	*s1 = "Hello World!";
	char	*s2 = "Hello xorld!";
	int		valid;
	int		ret;

	valid = strncmp(s1, s2, 6);
	ret = ft_strncmp(s1, s2, 6);

	v_assert_int(valid, ==, ret);

	VTS;
}

static void	test_05_strncmp_EmptyString(void)
{
	char	*s1 = "";
	char	*s2 = "Hello World!";
	int		valid;
	int		ret;

	valid = strncmp(s1, s2, 1);
	ret = ft_strncmp(s1, s2, 1);

#if defined(__APPLE__)
	(void)valid;
	v_assert_int(0, !=, ret);
#else
	v_assert_int(valid, ==, ret);
#endif

	VTS;
}

static void	test_06_strncmp_DoubleEmptyString(void)
{
	char	*s1 = "";
	char	*s2 = "";
	int		valid;
	int		ret;

	valid = strncmp(s1, s2, 1);
	ret = ft_strncmp(s1, s2, 1);

	v_assert_int(valid, ==, ret);

	VTS;
}

static void	test_07_strncmp_FirstCharDifferent(void)
{
	char	*s1 = "abcdef";
	char	*s2 = "bcdef";
	int		valid;
	int		ret;

	valid = strncmp(s1, s2, 2);
	ret = ft_strncmp(s1, s2, 2);

#if defined(__APPLE__)
	(void)valid;
	v_assert_int(0, !=, ret);
#else
	v_assert_int(valid, ==, ret);
#endif

	VTS;
}

static void	test_08_strncmp_LastCharDifferent(void)
{
	char	*s1 = "abcdef";
	char	*s2 = "abcdeg";
	int		valid;
	int		ret;

	valid = strncmp(s1, s2, 10);
	ret = ft_strncmp(s1, s2, 10);

#if defined(__APPLE__)
	(void)valid;
	v_assert_int(0, !=, ret);
#else
	v_assert_int(valid, ==, ret);
#endif

	VTS;
}

void	suite_strcmp(void)
{
	test_00_strcmp_EqualString();
	test_01_strcmp_UnequalString();
	test_02_strcmp_EmptyString();
	test_03_strcmp_DoubleEmptyString();
	test_04_strcmp_FirstCharDifferent();
	test_05_strcmp_LastCharDifferent();

	test_00_strncmp_EqualString();
	test_01_strncmp_UnequalString();
	test_03_strncmp_UnequalStringBeforeN();
	test_04_strncmp_UnequalStringAfterN();
	test_05_strncmp_EmptyString();
	test_06_strncmp_DoubleEmptyString();
	test_07_strncmp_FirstCharDifferent();
	test_08_strncmp_LastCharDifferent();

	VSS;
}
