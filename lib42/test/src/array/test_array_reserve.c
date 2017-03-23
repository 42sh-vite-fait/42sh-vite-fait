#include "header.h"

#define TEST_ARRAY_INIT_SIZE 8U

static t_array	*a;
static t_array	*pa;
static void	*comp;

static void setup(size_t len)
{
	a = malloc(sizeof(t_array));
	a->capacity = TEST_ARRAY_INIT_SIZE;
	a->len = len;
	a->elem_size = 16;
	a->data = malloc(a->capacity * a->elem_size);
	comp = malloc(a->capacity * a->elem_size);
	memset(a->data, '*', a->elem_size * a->len);
	memset(comp, '*', a->elem_size * a->len);

}

static void teardown(void)
{
	free(a->data);
	free(a);
	free(comp);
	a = NULL;
	pa = NULL;
	comp = NULL;
}

static void	test_00_array_reserve_LenZeroAddOne(void)
{
	setup(0);
	pa = array_reserve(a, 1);

	v_assert_ptr(pa, ==, a);
	v_assert_size_t(0, ==, a->len);
	v_assert_size_t(TEST_ARRAY_INIT_SIZE, ==, a->capacity);

	teardown();
	VTS;
}

static void	test_01_array_reserve_LenFullAddOne(void)
{
	setup(TEST_ARRAY_INIT_SIZE);
	pa = array_reserve(a, 1);

	v_assert_ptr(pa, ==, a);
	v_assert_size_t(TEST_ARRAY_INIT_SIZE, ==, a->len);
	v_assert_size_t(TEST_ARRAY_INIT_SIZE * 2, ==, a->capacity);

	int res = memcmp(a->data, comp, a->len * a->elem_size);
	v_assert_int(0, ==, res);

	teardown();
	VTS;
}

static void	test_02_array_reserve_LenZeroAddINIT_SIZE(void)
{
	setup(0);
	pa = array_reserve(a, TEST_ARRAY_INIT_SIZE);

	v_assert_ptr(pa, ==, a);
	v_assert_size_t(0, ==, a->len);
	v_assert_size_t(TEST_ARRAY_INIT_SIZE, ==, a->capacity);

	int res = memcmp(a->data, comp, a->len * a->elem_size);
	v_assert_int(0, ==, res);

	teardown();
	VTS;
}

static void	test_03_array_reserve_LenFullAddINIT_SIZE(void)
{
	setup(TEST_ARRAY_INIT_SIZE);
	pa = array_reserve(a, TEST_ARRAY_INIT_SIZE);

	v_assert_ptr(pa, ==, a);
	v_assert_size_t(TEST_ARRAY_INIT_SIZE, ==, a->len);
	v_assert_size_t(TEST_ARRAY_INIT_SIZE * 2, ==, a->capacity);

	int res = memcmp(a->data, comp, a->len * a->elem_size);
	v_assert_int(0, ==, res);

	teardown();
	VTS;
}

void suite_array_reserve(void)
{
	test_00_array_reserve_LenZeroAddOne();
	test_01_array_reserve_LenFullAddOne();
	test_02_array_reserve_LenZeroAddINIT_SIZE();
	test_03_array_reserve_LenFullAddINIT_SIZE();

	VSS;
}
