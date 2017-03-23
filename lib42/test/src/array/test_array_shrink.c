#include "header.h"

#define TEST_ARRAY_INIT_SIZE 8U

static t_array	*a;
static t_array	*pa;
static void		*comp;

static void setup(size_t len, size_t capacity)
{
	a = malloc(sizeof(t_array));
	a->capacity = capacity;
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

static void	test_00_array_shrink_ReduceBy4(void)
{
	setup(8, 32);
	void	*backup = a->data;
	pa = array_shrink_to_fit(a);

	v_assert_ptr(NULL, !=, pa);
	v_assert_ptr(a, ==, pa);
	v_assert_ptr(backup, !=, a->data);
	v_assert_size_t(8, ==, a->len);
	v_assert_size_t(8, ==, a->capacity);

	int res = memcmp(a->data, comp, a->len * a->elem_size);
	v_assert_int(0, ==, res);

	teardown();
	VTS;
}

static void	test_01_array_shrink_ReduceOnLenZeroCapacityAboveINIT_SIZE(void)
{
	setup(0, 64);
	void	*backup = a->data;
	pa = array_shrink_to_fit(a);

	v_assert_ptr(NULL, !=, pa);
	v_assert_ptr(a, ==, pa);
	v_assert_ptr(backup, !=, a->data);
	v_assert_size_t(0, ==, a->len);
	v_assert_size_t(8, ==, a->capacity);

	int res = memcmp(a->data, comp, a->len * a->elem_size);
	v_assert_int(0, ==, res);

	teardown();
	VTS;
}

static void	test_02_array_shrink_ReduceOnLenZeroCapacityEqualINIT_SIZE(void)
{
	setup(0, TEST_ARRAY_INIT_SIZE);
	void	*backup = a->data;
	pa = array_shrink_to_fit(a);

	v_assert_ptr(NULL, !=, pa);
	v_assert_ptr(a, ==, pa);
	v_assert_ptr(backup, ==, a->data);
	v_assert_size_t(0, ==, a->len);
	v_assert_size_t(8, ==, a->capacity);

	int res = memcmp(a->data, comp, a->len * a->elem_size);
	v_assert_int(0, ==, res);

	teardown();
	VTS;
}

static void	test_03_array_shrink_ReduceOnLenEqualCapacity(void)
{
	setup(16, 16);
	pa = array_shrink_to_fit(a);

	v_assert_ptr(NULL, !=, pa);
	v_assert_ptr(a, ==, pa);
	v_assert_size_t(16, ==, a->len);
	v_assert_size_t(16, ==, a->capacity);

	int res = memcmp(a->data, comp, a->len * a->elem_size);
	v_assert_int(0, ==, res);

	teardown();
	VTS;
}

void suite_array_shrink_to_fit(void)
{
	test_00_array_shrink_ReduceBy4();
	test_01_array_shrink_ReduceOnLenZeroCapacityAboveINIT_SIZE();
	test_02_array_shrink_ReduceOnLenZeroCapacityEqualINIT_SIZE();
	test_03_array_shrink_ReduceOnLenEqualCapacity();

	VSS;
}
