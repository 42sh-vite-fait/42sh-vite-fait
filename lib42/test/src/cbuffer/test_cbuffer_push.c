#include "header.h"

t_cbuffer	buffer;

static void		setup(size_t len, size_t elem_size, void (*del_func)(void *))
{
	buffer.data = malloc(len * elem_size);
	buffer.len = 0;
	buffer.capacity = len;
	buffer.elem_size = elem_size;
	buffer.delete_func = del_func;
	buffer.start = 0;
	buffer.end = 0;
}

static void		teardown(void)
{
	free(buffer.data);
}

static void	test_00_cbuffer_pushBackInt(void)
{
	setup(3, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	cbuffer_push_back(&buffer, &a);

	int back = *((int*)cbuffer_get_back(&buffer));
	v_assert_int(a, ==, back);

	int front = *((int*)cbuffer_get_front(&buffer));
	v_assert_int(a, ==, front);

	int n = *((int*)cbuffer_get_at(&buffer, 0));
	v_assert_int(a, ==, n);

	v_assert_size_t(1, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_01_cbuffer_pushBackTwoInt(void)
{
	setup(3, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	int b = 11;
	cbuffer_push_back(&buffer, &a);
	cbuffer_push_back(&buffer, &b);

	int front = *((int*)cbuffer_get_front(&buffer));
	v_assert_int(a, ==, front);

	int back = *((int*)cbuffer_get_back(&buffer));
	v_assert_int(b, ==, back);

	v_assert_size_t(2, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_02_cbuffer_pushBackExactLenInt(void)
{
	setup(3, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	int b = 11;
	int c = 12;
	cbuffer_push_back(&buffer, &a);
	cbuffer_push_back(&buffer, &b);
	cbuffer_push_back(&buffer, &c);

	int front = *((int*)cbuffer_get_front(&buffer));
	v_assert_int(a, ==, front);

	int middle = *((int*)cbuffer_get_at(&buffer, 1));
	v_assert_int(b, ==, middle);

	int back = *((int*)cbuffer_get_back(&buffer));
	v_assert_int(c, ==, back);

	v_assert_size_t(3, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_03_cbuffer_pushBackMoreInt(void)
{
	setup(3, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	int b = 11;
	int c = 12;
	int d = 13;
	cbuffer_push_back(&buffer, &a);
	cbuffer_push_back(&buffer, &b);
	cbuffer_push_back(&buffer, &c);
	cbuffer_push_back(&buffer, &d);

	int front = *((int*)cbuffer_get_front(&buffer));
	v_assert_int(b, ==, front);

	int middle = *((int*)cbuffer_get_at(&buffer, 1));
	v_assert_int(c, ==, middle);

	int back = *((int*)cbuffer_get_back(&buffer));
	v_assert_int(d, ==, back);

	v_assert_size_t(3, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_04_cbuffer_pushFrontInt(void)
{
	setup(3, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	cbuffer_push_front(&buffer, &a);

	int front = *((int*)cbuffer_get_front(&buffer));
	v_assert_int(a, ==, front);

	int n = *((int*)cbuffer_get_at(&buffer, 0));
	v_assert_int(a, ==, n);

	int back = *((int*)cbuffer_get_back(&buffer));
	v_assert_int(a, ==, back);

	v_assert_size_t(1, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_05_cbuffer_pushFrontTwoInt(void)
{
	setup(3, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	int b = 11;
	cbuffer_push_front(&buffer, &a);
	cbuffer_push_front(&buffer, &b);

	int front = *((int*)cbuffer_get_front(&buffer));
	v_assert_int(b, ==, front);

	int n1 = *((int*)cbuffer_get_at(&buffer, 0));
	v_assert_int(b, ==, n1);

	int n2 = *((int*)cbuffer_get_at(&buffer, 1));
	v_assert_int(a, ==, n2);

	int back = *((int*)cbuffer_get_back(&buffer));
	v_assert_int(a, ==, back);

	v_assert_size_t(2, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_06_cbuffer_pushFrontExactLenInt(void)
{
	setup(3, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	int b = 11;
	int c = 12;
	cbuffer_push_front(&buffer, &a);
	cbuffer_push_front(&buffer, &b);
	cbuffer_push_front(&buffer, &c);

	int front = *((int*)cbuffer_get_front(&buffer));
	v_assert_int(c, ==, front);

	int middle = *((int*)cbuffer_get_at(&buffer, 1));
	v_assert_int(b, ==, middle);

	int back = *((int*)cbuffer_get_back(&buffer));
	v_assert_int(a, ==, back);

	v_assert_size_t(3, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_07_cbuffer_pushFrontMoreInt(void)
{
	setup(3, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	int b = 11;
	int c = 12;
	int d = 13;
	cbuffer_push_front(&buffer, &a);
	cbuffer_push_front(&buffer, &b);
	cbuffer_push_front(&buffer, &c);
	cbuffer_push_front(&buffer, &d);

	int front = *((int*)cbuffer_get_front(&buffer));
	v_assert_int(d, ==, front);

	int middle = *((int*)cbuffer_get_at(&buffer, 1));
	v_assert_int(c, ==, middle);

	int back = *((int*)cbuffer_get_back(&buffer));
	v_assert_int(b, ==, back);

	v_assert_size_t(3, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void test_08_cbuffer_pushFrontAndBackInt(void)
{
	setup(3, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	int b = 11;
	cbuffer_push_back(&buffer, &a);
	cbuffer_push_front(&buffer, &b);

	int front = *((int*)cbuffer_get_front(&buffer));
	v_assert_int(b, ==, front);

	int n1 = *((int*)cbuffer_get_at(&buffer, 0));
	v_assert_int(b, ==, n1);

	int n2 = *((int*)cbuffer_get_at(&buffer, 1));
	v_assert_int(a, ==, n2);

	int back = *((int*)cbuffer_get_back(&buffer));
	v_assert_int(a, ==, back);

	v_assert_size_t(2, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void test_09_cbuffer_pushFrontAndBackTwoInt(void)
{
	setup(3, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	int b = 11;
	int c = 12;
	int d = 13;
	cbuffer_push_front(&buffer, &a);
	cbuffer_push_front(&buffer, &b);
	cbuffer_push_back(&buffer, &c);
	cbuffer_push_back(&buffer, &d);

	int front = *((int*)cbuffer_get_front(&buffer));
	v_assert_int(a, ==, front);

	int n1 = *((int*)cbuffer_get_at(&buffer, 0));
	v_assert_int(a, ==, n1);

	int n2 = *((int*)cbuffer_get_at(&buffer, 1));
	v_assert_int(c, ==, n2);

	int n3 = *((int*)cbuffer_get_at(&buffer, 2));
	v_assert_int(d, ==, n3);

	int back = *((int*)cbuffer_get_back(&buffer));
	v_assert_int(d, ==, back);

	v_assert_size_t(3, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void test_10_cbuffer_pushBackAndFrontInt(void)
{
	setup(3, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	int b = 11;
	cbuffer_push_back(&buffer, &a);
	cbuffer_push_front(&buffer, &b);

	int front = *((int*)cbuffer_get_front(&buffer));
	v_assert_int(b, ==, front);

	int back = *((int*)cbuffer_get_back(&buffer));
	v_assert_int(a, ==, back);

	v_assert_size_t(2, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void test_11_cbuffer_pushBackAndFrontTwoInt(void)
{
	setup(3, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	int b = 11;
	int c = 12;
	int d = 13;
	cbuffer_push_back(&buffer, &a);
	cbuffer_push_back(&buffer, &b);
	cbuffer_push_front(&buffer, &c);
	cbuffer_push_front(&buffer, &d);

	int front = *((int*)cbuffer_get_front(&buffer));
	v_assert_int(d, ==, front);

	int n1 = *((int*)cbuffer_get_at(&buffer, 0));
	v_assert_int(d, ==, n1);

	int n2 = *((int*)cbuffer_get_at(&buffer, 1));
	v_assert_int(c, ==, n2);

	int n3 = *((int*)cbuffer_get_at(&buffer, 2));
	v_assert_int(a, ==, n3);

	int back = *((int*)cbuffer_get_back(&buffer));
	v_assert_int(a, ==, back);

	v_assert_size_t(3, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	delete_func(void *n)
{
	**((int**)n) = 22;
}

static void	test_12_cbuffer_pushBackCallDelete(void)
{
	setup(3, sizeof(int*), delete_func);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	int b = 11;
	int c = 12;
	int d = 13;

	int *a_ptr = &a;
	int *b_ptr = &b;
	int *c_ptr = &c;
	int *d_ptr = &d;
	cbuffer_push_back(&buffer, &a_ptr);
	cbuffer_push_back(&buffer, &b_ptr);
	cbuffer_push_back(&buffer, &c_ptr);
	cbuffer_push_back(&buffer, &d_ptr);

	int *front = *((int**)cbuffer_get_front(&buffer));
	v_assert_ptr(b_ptr, ==, front);
	v_assert_int(b, ==, *front);

	int *middle = *((int**)cbuffer_get_at(&buffer, 1));
	v_assert_ptr(c_ptr, ==, middle);
	v_assert_int(c, ==, *middle);

	int *back = *((int**)cbuffer_get_back(&buffer));
	v_assert_ptr(d_ptr, ==, back);
	v_assert_int(d, ==, *back);

	v_assert_int(a, ==, 22);

	v_assert_size_t(3, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_13_cbuffer_pushFrontCallDelete(void)
{
	setup(3, sizeof(int*), delete_func);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	int b = 11;
	int c = 12;
	int d = 13;

	int *a_ptr = &a;
	int *b_ptr = &b;
	int *c_ptr = &c;
	int *d_ptr = &d;
	cbuffer_push_front(&buffer, &a_ptr);
	cbuffer_push_front(&buffer, &b_ptr);
	cbuffer_push_front(&buffer, &c_ptr);
	cbuffer_push_front(&buffer, &d_ptr);

	int *front = *((int**)cbuffer_get_front(&buffer));
	v_assert_ptr(d_ptr, ==, front);
	v_assert_int(d, ==, *front);

	int *middle = *((int**)cbuffer_get_at(&buffer, 1));
	v_assert_ptr(c_ptr, ==, middle);
	v_assert_int(c, ==, *middle);

	int *back = *((int**)cbuffer_get_back(&buffer));
	v_assert_ptr(b_ptr, ==, back);
	v_assert_int(b, ==, *back);

	v_assert_int(a, ==, 22);

	v_assert_size_t(3, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_14_cbuffer_pushFrontStrings(void)
{
	setup(3, sizeof(char*), NULL);

	const char	*str_hello = "hello";
	const char	*str_bonjour = "bonjour";
	const char	*str_holla = "holla";

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	cbuffer_push_front(&buffer, &str_hello);
	cbuffer_push_front(&buffer, &str_bonjour);
	cbuffer_push_front(&buffer, &str_holla);

	char **front = cbuffer_get_front(&buffer);
	v_assert_str(str_holla, *front);

	char **n = cbuffer_get_at(&buffer, 1);
	v_assert_str(str_bonjour, *n);

	char **back = cbuffer_get_back(&buffer);
	v_assert_str(str_hello, *back);

	v_assert_size_t(3, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_14_cbuffer_pushBackStrings(void)
{
	setup(3, sizeof(char*), NULL);

	const char	*str_hello = "hello";
	const char	*str_bonjour = "bonjour";
	const char	*str_holla = "holla";

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	cbuffer_push_back(&buffer, &str_hello);
	cbuffer_push_back(&buffer, &str_bonjour);
	cbuffer_push_back(&buffer, &str_holla);

	char **front = cbuffer_get_front(&buffer);
	v_assert_str(str_hello, *front);

	char **n = cbuffer_get_at(&buffer, 1);
	v_assert_str(str_bonjour, *n);

	char **back = cbuffer_get_back(&buffer);
	v_assert_str(str_holla, *back);

	v_assert_size_t(3, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

void	suite_cbuffer_push(void)
{
	test_00_cbuffer_pushBackInt();
	test_01_cbuffer_pushBackTwoInt();
	test_02_cbuffer_pushBackExactLenInt();
	test_03_cbuffer_pushBackMoreInt();

	test_04_cbuffer_pushFrontInt();
	test_05_cbuffer_pushFrontTwoInt();
	test_06_cbuffer_pushFrontExactLenInt();
	test_07_cbuffer_pushFrontMoreInt();

	test_08_cbuffer_pushFrontAndBackInt();
	test_09_cbuffer_pushFrontAndBackTwoInt();

	test_10_cbuffer_pushBackAndFrontInt();
	test_11_cbuffer_pushBackAndFrontTwoInt();

	test_12_cbuffer_pushBackCallDelete();
	test_13_cbuffer_pushFrontCallDelete();

	test_14_cbuffer_pushFrontStrings();
	test_14_cbuffer_pushBackStrings();

	VSS;
}
