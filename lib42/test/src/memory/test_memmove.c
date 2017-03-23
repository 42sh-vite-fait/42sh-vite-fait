#include "header.h"

static void	test_00_memmove_SizeZero(void)
{
	char	s1[20];
	char	bs1[20];
	char	s2[20];
	char	bs2[20];
	void	*res;

	memset(s1, '*', 20);
	memset(bs1, '*', 20);
	memset(s2, '#', 20);
	memset(bs2, '#', 20);
	res = ft_memmove(s2, s1, 0);

	v_assert_ptr(s2, ==, res);
	v_assert(memcmp(s1, bs1, 20) == 0);
	v_assert(memcmp(s2, bs2, 20) == 0);

	VTS;
}

static void	test_01_memmove_DstAfterSimpleString(void)
{
	char	s1[13] = "Hello World!";
	void	*res;

	res = ft_memmove(s1 + 6, s1, 5);

	v_assert_ptr(s1 + 6, ==, res);
	v_assert_str("Hello Hello!", s1);

	VTS;
}

static void	test_02_memmove_DstBeforeSimpleString(void)
{
	char	s1[13] = "Hello World!";
	char	*s2;
	void	*res;

	res = ft_memmove(s1, s1 + 6, 5);

	v_assert_ptr(s1, ==, res);
	v_assert_str("World World!", s1);

	VTS;
}

static void	test_03_memmove_DstAfterSrcCheckBorder(void)
{
	size_t	size = 100;
	char	*s = malloc(size);
	void	*res;

	memset(s, '*', size);
	s[0] = '#';
	s[99] = '#';
	res = ft_memmove(s + 1, s, 100 - 2);

	v_assert_ptr(s + 1, ==, res);
	v_assert_char('#', ==, s[0]);
	v_assert_char('#', ==, s[99]);

	free(s);
	VTS;
}

static void	test_04_memmove_DstAfterSrcBigChunks(void)
{
	char	*s = malloc(BIG_CHUNKS);
	void	*res;

	memset(s, '*', BIG_CHUNKS);
	s[0] = '#';
	res = ft_memmove(s + 1, s, BIG_CHUNKS - 1);

	v_assert_ptr(s + 1, ==, res);
	v_assert_char('#', ==, s[0]);

	free(s);
	VTS;
}

void		suite_memmove(void)
{
	test_00_memmove_SizeZero();
	test_01_memmove_DstAfterSimpleString();
	test_02_memmove_DstBeforeSimpleString();
	test_03_memmove_DstAfterSrcCheckBorder();
	test_04_memmove_DstAfterSrcBigChunks();

	VSS;
}
