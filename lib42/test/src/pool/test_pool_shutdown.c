#include "header.h"

static t_pool	*p;

static void	setup(size_t size)
{
	p = pool_create(size);
}

static void	teardown(void)
{
	void	*ptr;

	while ((ptr = p->chunks_list))
	{
		p->chunks_list = p->chunks_list->next;
		free(ptr);
	}
	free(p);
}

static void	test_00_pool_shutdown_MultiChunksInPool(void)
{
	size_t	elem_size = sizeof(char*);

	// setup
	setup(elem_size);
	for (size_t i = 0; i < 6; ++i)
	{
		pool_obtain_node(p);
	}

	// shutdown du pool
	pool_shutdown(p);
	v_assert_ptr(NULL, ==, p->free_list);
	v_assert_ptr(NULL, ==, p->chunks_list);
	v_assert_size_t(sizeof(char*), ==, p->elem_size);
	v_assert_size_t(511, ==, p->chunk_capacity);

	teardown();
	VTS;
}

static void test_01_pool_shutdown_NewAllocAftershutdown(void)
{
	size_t	elem_size = sizeof(char*);
	size_t	count = 1;
	void	*pValue[6];

	// setup
	setup(elem_size);
	for (size_t i = 0; i < 6; ++i)
	{
		pValue[i] = pool_obtain_node(p);
		pValue[i] = "Hello World!";
		v_assert_str("Hello World!", pValue[i]);
	}

	// shutdown du pool
	pool_shutdown(p);
	v_assert_ptr(NULL, ==, p->free_list);
	v_assert_ptr(NULL, ==, p->chunks_list);
	v_assert_size_t(sizeof(char*), ==, p->elem_size);
	v_assert_size_t(511, ==, p->chunk_capacity);

	// nouvelle allocation
	pValue[0] = pool_obtain_node(p);
	pValue[0] = "New alloc";
	v_assert_str("New alloc", pValue[0]);

	teardown();
	VTS;
}

void	suite_pool_shutdown(void)
{
	test_00_pool_shutdown_MultiChunksInPool();
	test_01_pool_shutdown_NewAllocAftershutdown();

	VSS;
}
