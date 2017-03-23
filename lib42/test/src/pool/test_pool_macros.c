#include "header.h"

static void test_00_pool_ROUND_UP_8(void)
{
	size_t	res;

	res = ROUND_UP_8(0U);
	v_assert_size_t(8, ==, res);

	res = ROUND_UP_8(1U);
	v_assert_size_t(8, ==, res);

	res = ROUND_UP_8(7U);
	v_assert_size_t(8, ==, res);

	res = ROUND_UP_8(8U);
	v_assert_size_t(8, ==, res);

	res = ROUND_UP_8(13U);
	v_assert_size_t(16, ==, res);

	res = ROUND_UP_8(15U);
	v_assert_size_t(16, ==, res);

	res = ROUND_UP_8(16U);
	v_assert_size_t(16, ==, res);

	res = ROUND_UP_8(21U);
	v_assert_size_t(24, ==, res);

	VTS;
}

static void	test_01_pool_CHUNK_CAPACITY(void)
{
	size_t	res;

	res = CHUNK_CAPACITY(ROUND_UP_8(sizeof(int)));
	v_assert_size_t(511, ==, res);

	res = CHUNK_CAPACITY(ROUND_UP_8(13));
	v_assert_size_t(255, ==, res);

	res = CHUNK_CAPACITY(ROUND_UP_8(39));
	v_assert_size_t(102, ==, res);

	VTS;
}

static void	test_02_pool_CHUNK_HEAD(void)
{
	t_chunk	chunk;
	void	*p1;
	void	*p2;

	p1 = CHUNK_HEAD(&chunk);
	p2 = (unsigned char*)&chunk + sizeof(void*);
	v_assert_ptr(&chunk.head, ==, p2);
	v_assert_ptr(p2, ==, p1);

	VTS;
}

void	suite_pool_macros(void)
{
	test_00_pool_ROUND_UP_8();
	test_01_pool_CHUNK_CAPACITY();
	test_02_pool_CHUNK_HEAD();

	VSS;
}
