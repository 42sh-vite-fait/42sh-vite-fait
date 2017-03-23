#include "header.h"

#define TEST_ARRAY_INIT_SIZE 8U

static t_array	*a;

static void teardown(void)
{
	if (a != NULL)
	{
		free(a->data);
		free(a);
	}
	a = NULL;
}

// array_create
static void	test_00_array_create_ElemSizeZero(void)
{
	a = array_create(0);

	v_assert_ptr(NULL, ==, a);

	teardown();
	VTS;
}

static void	test_01_array_create_ElemSizeOne(void)
{
	a = array_create(1);

	v_assert_ptr(NULL, !=, a);
	v_assert_size_t(1, ==, a->elem_size);
	v_assert_size_t(0, ==, a->len);
	v_assert_size_t(TEST_ARRAY_INIT_SIZE, ==, a->capacity);

	teardown();
	VTS;
}

static void	test_02_array_create_ElemSize21(void)
{
	a = array_create(21);

	v_assert_ptr(NULL, !=, a);
	v_assert_size_t(21, ==, a->elem_size);
	v_assert_size_t(0, ==, a->len);
	v_assert_size_t(TEST_ARRAY_INIT_SIZE, ==, a->capacity);

	teardown();
	VTS;
}

// array_create_with_capacity
static void	test_00_array_create_with_capacity_ElemSizeZeroCapacityZero(void)
{
	a = array_create_with_capacity(0, 0);

	v_assert_ptr(NULL, ==, a);

	teardown();
	VTS;
}

static void	test_01_array_create_with_capacity_ElemSizeOneCapacityZero(void)
{
	a = array_create_with_capacity(1, 0);

	v_assert_ptr(NULL, !=, a);
	v_assert_size_t(1, ==, a->elem_size);
	v_assert_size_t(0, ==, a->len);
	v_assert_size_t(TEST_ARRAY_INIT_SIZE, ==, a->capacity);

	teardown();
	VTS;
}

static void	test_02_array_create_with_capacity_ElemSize21CapacityZero(void)
{
	a = array_create_with_capacity(21, 0);

	v_assert_ptr(NULL, !=, a);
	v_assert_size_t(21, ==, a->elem_size);
	v_assert_size_t(0, ==, a->len);
	v_assert_size_t(TEST_ARRAY_INIT_SIZE, ==, a->capacity);

	teardown();
	VTS;
}

static void	test_03_array_create_with_capacity_ElemSizeIntCapacityOverINIT_SIZE(void)
{
	a = array_create_with_capacity(sizeof(int), TEST_ARRAY_INIT_SIZE + 1);

	v_assert_ptr(NULL, !=, a);
	v_assert_size_t(sizeof(int), ==, a->elem_size);
	v_assert_size_t(0, ==, a->len);
	v_assert_size_t(TEST_ARRAY_INIT_SIZE * 2, ==, a->capacity);

	teardown();
	VTS;
}

static void	test_04_array_create_with_capacity_ElemSizeIntCapacityUnderINIT_SIZE(void)
{
	a = array_create_with_capacity(sizeof(int), 1);

	v_assert_ptr(NULL, !=, a);
	v_assert_size_t(sizeof(int), ==, a->elem_size);
	v_assert_size_t(0, ==, a->len);
	v_assert_size_t(TEST_ARRAY_INIT_SIZE, ==, a->capacity);

	teardown();
	VTS;
}

static void	test_05_array_create_with_capacity_ElemSizeIntCapacityEqualINIT_SIZE(void)
{
	a = array_create_with_capacity(sizeof(int), TEST_ARRAY_INIT_SIZE);

	v_assert_ptr(NULL, !=, a);
	v_assert_size_t(sizeof(int), ==, a->elem_size);
	v_assert_size_t(0, ==, a->len);
	v_assert_size_t(TEST_ARRAY_INIT_SIZE, ==, a->capacity);

	teardown();
	VTS;
}

void suite_array_create(void)
{
	test_00_array_create_ElemSizeZero();
	test_01_array_create_ElemSizeOne();
	test_02_array_create_ElemSize21();

	test_00_array_create_with_capacity_ElemSizeZeroCapacityZero();
	test_01_array_create_with_capacity_ElemSizeOneCapacityZero();
	test_02_array_create_with_capacity_ElemSize21CapacityZero();
	test_03_array_create_with_capacity_ElemSizeIntCapacityOverINIT_SIZE();
	test_04_array_create_with_capacity_ElemSizeIntCapacityUnderINIT_SIZE();
	test_05_array_create_with_capacity_ElemSizeIntCapacityEqualINIT_SIZE();

	VSS;
}
