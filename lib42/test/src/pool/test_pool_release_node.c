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

static void	test_00_pool_release_node_AllElementTypeUnsignedIntInOrder(void)
{
	size_t	elem_size = sizeof(unsigned);
	char	*pAddr;

	// setup
	setup(elem_size);
	void	*pValue[p->chunk_capacity];

	// get each nodes
	for (size_t i = 0; i < p->chunk_capacity; ++i)
		pValue[i] = pool_obtain_node(p);
	v_assert_ptr(NULL, ==, p->free_list);

	// test
	for (size_t i = 0; i < p->chunk_capacity; ++i)
	{
		pool_release_node(p, pValue[i]);
		v_assert_ptr(pValue[i], ==, p->free_list);
	}

	teardown();
	VTS;
}

static void	test_01_pool_release_node_AllElementTypeUnsignedIntInDisorder(void)
{
	size_t	elem_size = sizeof(unsigned);
	char	*pAddr;

	// setup
	setup(elem_size);
	void	*pValue[p->chunk_capacity];

	// get each nodes
	for (size_t i = 0; i < p->chunk_capacity; ++i)
		pValue[i] = pool_obtain_node(p);
	v_assert_ptr(NULL, ==, p->free_list);

	// test
	pool_release_node(p, pValue[3]);
	v_assert_ptr(pValue[3], ==, p->free_list);
	pool_release_node(p, pValue[1]);
	v_assert_ptr(pValue[1], ==, p->free_list);
	pool_release_node(p, pValue[0]);
	v_assert_ptr(pValue[0], ==, p->free_list);
	pool_release_node(p, pValue[4]);
	v_assert_ptr(pValue[4], ==, p->free_list);
	pool_release_node(p, pValue[2]);
	v_assert_ptr(pValue[2], ==, p->free_list);

	// obtain
	void	*pObtain = pool_obtain_node(p);
	v_assert_ptr(pValue[2], ==, pObtain);
	pObtain = pool_obtain_node(p);
	v_assert_ptr(pValue[4], ==, pObtain);
	pObtain = pool_obtain_node(p);
	v_assert_ptr(pValue[0], ==, pObtain);
	pObtain = pool_obtain_node(p);
	v_assert_ptr(pValue[1], ==, pObtain);
	pObtain = pool_obtain_node(p);
	v_assert_ptr(pValue[3], ==, pObtain);

	teardown();
	VTS;
}

static void	test_02_pool_release_node_MultiChunksInDisorder(void)
{
	size_t	elem_size = 4000;
	char	*pAddr;

	// test
	setup(elem_size);
	v_assert_size_t(1, ==,  p->chunk_capacity);
	void	*pValue[3];

	// get each nodes
	for (size_t i = 0; i < 3; ++i)
		pValue[i] = pool_obtain_node(p);
	v_assert_ptr(NULL, ==, p->free_list);

	// test
	pool_release_node(p, pValue[1]);
	v_assert_ptr(pValue[1], ==, p->free_list);
	pool_release_node(p, pValue[2]);
	v_assert_ptr(pValue[2], ==, p->free_list);
	pool_release_node(p, pValue[0]);
	v_assert_ptr(pValue[0], ==, p->free_list);

	// obtain
	void	*pObtain = pool_obtain_node(p);
	v_assert_ptr(pValue[0], ==, pObtain);
	pObtain = pool_obtain_node(p);
	v_assert_ptr(pValue[2], ==, pObtain);
	pObtain = pool_obtain_node(p);
	v_assert_ptr(pValue[1], ==, pObtain);

	teardown();
	VTS;
}

void	suite_pool_release_node(void)
{
	test_00_pool_release_node_AllElementTypeUnsignedIntInOrder();
	test_01_pool_release_node_AllElementTypeUnsignedIntInDisorder();
	test_02_pool_release_node_MultiChunksInDisorder();

	VSS;
}
