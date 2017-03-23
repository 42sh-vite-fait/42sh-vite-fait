#include "header.h"

#define TEST_ARRAY_INIT_SIZE 8U

static t_array	a;
static t_array	*pa;

static void teardown(void)
{
	free(a.data);
	memset(&a, 0, sizeof(t_array));
}

// array_init
static void	test_00_array_init_ElemSizeZero(void)
{
	pa = array_init(&a, 0);

	v_assert_ptr(NULL, ==, pa);

	teardown();
	VTS;
}

static void	test_01_array_init_ElemSizeOne(void)
{
	pa = array_init(&a, 1);

	v_assert_ptr(NULL, !=, pa);
	v_assert_ptr(&a, ==, pa);
	v_assert_size_t(1, ==, pa->elem_size);
	v_assert_size_t(0, ==, pa->len);
	v_assert_size_t(TEST_ARRAY_INIT_SIZE, ==, pa->capacity);

	teardown();
	VTS;
}

static void	test_02_array_init_ElemSize21(void)
{
	pa = array_init(&a, 21);

	v_assert_ptr(NULL, !=, pa);
	v_assert_ptr(&a, ==, pa);
	v_assert_size_t(21, ==, pa->elem_size);
	v_assert_size_t(0, ==, pa->len);
	v_assert_size_t(TEST_ARRAY_INIT_SIZE, ==, pa->capacity);

	teardown();
	VTS;
}

// array_init_with_capacity
static void	test_00_array_init_with_capacity_ElemSizeZeroCapacityZero(void)
{
	pa = array_init_with_capacity(&a, 0, 0);

	v_assert_ptr(NULL, ==, pa);

	teardown();
	VTS;
}

static void	test_01_array_init_with_capacity_ElemSizeOneCapacityZero(void)
{
	pa = array_init_with_capacity(&a, 1, 0);

	v_assert_ptr(NULL, !=, pa);
	v_assert_ptr(&a, ==, pa);
	v_assert_size_t(1, ==, pa->elem_size);
	v_assert_size_t(0, ==, pa->len);
	v_assert_size_t(TEST_ARRAY_INIT_SIZE, ==, pa->capacity);

	teardown();
	VTS;
}

static void	test_02_array_init_with_capacity_ElemSize21CapacityZero(void)
{
	pa = array_init_with_capacity(&a, 21, 0);

	v_assert_ptr(NULL, !=, pa);
	v_assert_ptr(&a, ==, pa);
	v_assert_size_t(21, ==, pa->elem_size);
	v_assert_size_t(0, ==, pa->len);
	v_assert_size_t(TEST_ARRAY_INIT_SIZE, ==, pa->capacity);

	teardown();
	VTS;
}

static void	test_03_array_init_with_capacity_ElemSizeIntCapacityOverINIT_SIZE(void)
{
	pa = array_init_with_capacity(&a, sizeof(int), TEST_ARRAY_INIT_SIZE + 1);

	v_assert_ptr(NULL, !=, pa);
	v_assert_ptr(&a, ==, pa);
	v_assert_size_t(sizeof(int), ==, pa->elem_size);
	v_assert_size_t(0, ==, pa->len);
	v_assert_size_t(TEST_ARRAY_INIT_SIZE * 2, ==, pa->capacity);

	teardown();
	VTS;
}

static void	test_04_array_init_with_capacity_ElemSizeIntCapacityUnderINIT_SIZE(void)
{
	pa = array_init_with_capacity(&a, sizeof(int), 1);

	v_assert_ptr(NULL, !=, pa);
	v_assert_ptr(&a, ==, pa);
	v_assert_size_t(sizeof(int), ==, pa->elem_size);
	v_assert_size_t(0, ==, pa->len);
	v_assert_size_t(TEST_ARRAY_INIT_SIZE, ==, pa->capacity);

	teardown();
	VTS;
}

static void	test_05_array_init_with_capacity_ElemSizeIntCapacityEqualINIT_SIZE(void)
{
	pa = array_init_with_capacity(&a, sizeof(int), TEST_ARRAY_INIT_SIZE);

	v_assert_ptr(NULL, !=, pa);
	v_assert_ptr(&a, ==, pa);
	v_assert_size_t(sizeof(int), ==, pa->elem_size);
	v_assert_size_t(0, ==, pa->len);
	v_assert_size_t(TEST_ARRAY_INIT_SIZE, ==, pa->capacity);

	teardown();
	VTS;
}

void suite_array_init(void)
{
	test_00_array_init_ElemSizeZero();
	test_01_array_init_ElemSizeOne();
	test_02_array_init_ElemSize21();

	test_00_array_init_with_capacity_ElemSizeZeroCapacityZero();
	test_01_array_init_with_capacity_ElemSizeOneCapacityZero();
	test_02_array_init_with_capacity_ElemSize21CapacityZero();
	test_03_array_init_with_capacity_ElemSizeIntCapacityOverINIT_SIZE();
	test_04_array_init_with_capacity_ElemSizeIntCapacityUnderINIT_SIZE();
	test_05_array_init_with_capacity_ElemSizeIntCapacityEqualINIT_SIZE();

	VSS;
}
