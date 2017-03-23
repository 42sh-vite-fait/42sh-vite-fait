#include "header.h"

static t_string		string;

static void	test_00_string_init_SizeBelowMinimum(void)
{
	string_init_with_capacity(&string, 4);

	v_assert_size_t(STRING_INIT_SIZE, ==, string.capacity);

	string_shutdown(&string);
	VTS;
}

static void	test_01_string_init_SizeAboveMinimum(void)
{
	string_init_with_capacity(&string, 1111);

	v_assert_size_t(2048, ==, string.capacity);

	string_shutdown(&string);
	VTS;
}

static void	test_02_string_init_SizePowerOf2(void)
{
	string_init_with_capacity(&string, 256);

	v_assert_size_t(512, ==, string.capacity);

	string_shutdown(&string);
	VTS;
}

static void	test_03_string_init_SizeOfInit(void)
{
	string_init_with_capacity(&string, STRING_INIT_SIZE);

	v_assert_size_t(next_power_of_2(STRING_INIT_SIZE), ==, string.capacity);

	string_shutdown(&string);
	VTS;
}

static void	test_04_string_init_SizePowerOf2MinsOne(void)
{
	string_init_with_capacity(&string, 255);

	v_assert_size_t(256, ==, string.capacity);

	string_shutdown(&string);
	VTS;
}

static void	test_05_string_create_SizeBelowMinimum(void)
{
	t_string *string = string_create_with_capacity(4);

	v_assert_size_t(STRING_INIT_SIZE, ==, string->capacity);

	string_destroy(string);
	VTS;
}

static void	test_06_string_create_SizeAboveMinimum(void)
{
	t_string *string = string_create_with_capacity(1111);

	v_assert_size_t(2048, ==, string->capacity);

	string_destroy(string);
	VTS;
}

static void	test_07_string_create_SizePowerOf2(void)
{
	t_string *string = string_create_with_capacity(256);

	v_assert_size_t(512, ==, string->capacity);

	string_destroy(string);
	VTS;
}

static void	test_08_string_create_SizeOfInit(void)
{
	t_string *string = string_create_with_capacity(STRING_INIT_SIZE);

	v_assert_size_t(next_power_of_2(STRING_INIT_SIZE), ==, string->capacity);

	string_destroy(string);
	VTS;
}

static void	test_09_string_create_SizePowerOf2MinsOne(void)
{
	t_string *string = string_create_with_capacity(255);

	v_assert_size_t(256, ==, string->capacity);

	string_destroy(string);
	VTS;
}

static void	test_10_string_init_default_size(void)
{
	string_init(&string);

	v_assert_size_t(STRING_INIT_SIZE, ==, string.capacity);

	string_shutdown(&string);
	VTS;
}
static void	test_11_string_create_default_size(void)
{
	t_string *string = string_create();

	v_assert_size_t(STRING_INIT_SIZE, ==, string->capacity);

	string_destroy(string);
	VTS;
}

void	suite_string_create_init(void)
{
	test_00_string_init_SizeBelowMinimum();
	test_01_string_init_SizeAboveMinimum();
	test_02_string_init_SizePowerOf2();
	test_03_string_init_SizeOfInit();
	test_04_string_init_SizePowerOf2MinsOne();

	test_05_string_create_SizeBelowMinimum();
	test_06_string_create_SizeAboveMinimum();
	test_07_string_create_SizePowerOf2();
	test_08_string_create_SizeOfInit();
	test_09_string_create_SizePowerOf2MinsOne();

	test_10_string_init_default_size();
	test_11_string_create_default_size();

	VSS;
}
