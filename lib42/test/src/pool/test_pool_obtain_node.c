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

static void	test_00_pool_obtain_node_UsageWithUnsignedInt(void)
{
	size_t	elem_size = sizeof(unsigned);
	void	*pValue;

	setup(elem_size);

	for (size_t i = 0; i < p->chunk_capacity - 1; ++i)
	{
		pValue = pool_obtain_node(p);
		v_assert_ptr(NULL, !=, pValue);
		v_assert_ptr(*(uintptr_t*)pValue, ==, (char*)pValue + p->elem_size);
		*(unsigned*)pValue = '*';
		v_assert_uint('*', ==, *(unsigned*)pValue);
	}
	// last free node
	pValue = pool_obtain_node(p);
	v_assert_ptr(NULL, !=, pValue);
	v_assert_uintptr(0, ==, *(uintptr_t*)pValue);
	*(unsigned*)pValue = '*';
	v_assert_uint('*', ==, *(unsigned*)pValue);

	// Fin du chunk
	v_assert_ptr(NULL, ==, p->free_list);

	// Creation d'un nouveau chunk
	pValue = pool_obtain_node(p);
	v_assert_ptr(NULL, !=, p->free_list);
	v_assert_ptr(NULL, !=, pValue);
	*(unsigned*)pValue = '*';
	(void)pValue;

	teardown();
	VTS;
}

static void	test_01_pool_obtain_node_UsageWithArbitratyStruct(void)
{
	struct s_pool_test {
		void	*p;
		long	l;
		char	c[3];
	} t;
	size_t	elem_size = sizeof(struct s_pool_test);
	void	*pValue;

	setup(elem_size);

	for (size_t i = 0; i < p->chunk_capacity - 1; ++i)
	{
		pValue = pool_obtain_node(p);
		v_assert_ptr(NULL, !=, pValue);
		v_assert_ptr(*(uintptr_t*)pValue, ==, (char*)pValue + p->elem_size);
		*(struct s_pool_test*)pValue = (struct s_pool_test){
			.p = (void*)i, .l = (long)i,
		};
		v_assert_ptr(i, ==, ((struct s_pool_test*)pValue)->p);
		v_assert_long(i, ==, ((struct s_pool_test*)pValue)->l);
	}
	// last free node
	pValue = pool_obtain_node(p);
	v_assert_ptr(NULL, !=, pValue);
	v_assert_uintptr(0, ==, *(uintptr_t*)pValue);

	// Fin du chunk
	v_assert_ptr(NULL, ==, p->free_list);

	// Creation d'un nouveau chunk
	pValue = pool_obtain_node(p);
	v_assert_ptr(NULL, !=, p->free_list);
	v_assert_ptr(NULL, !=, pValue);
	*(struct s_pool_test*)pValue = (struct s_pool_test){
		.p = (void*)0xdeadbeef, .l = (long)~0,
	};
	v_assert_ptr(0xdeadbeef, ==, ((struct s_pool_test*)pValue)->p);
	v_assert_long(~0, ==, ((struct s_pool_test*)pValue)->l);

	teardown();
	VTS;
}

void	suite_pool_obtain_node(void)
{
	test_00_pool_obtain_node_UsageWithUnsignedInt();
	test_01_pool_obtain_node_UsageWithArbitratyStruct();

	VSS;
}
