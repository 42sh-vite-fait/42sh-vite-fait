#include "header.h"

static t_pool	pool;
static t_pool	*p;

static void	teardown(void)
{
	void	*tmp;

	while (pool.chunks_list)
	{
		tmp = pool.chunks_list;
		pool.chunks_list = pool.chunks_list->next;
		free(tmp);
	}
}

static void	test_00_pool_init_ArgEqualZero(void)
{
	p = pool_init(&pool, 0);
	v_assert_ptr(NULL, ==, p);

	VTS;
}

static void	test_01_pool_init_SizeOfInt(void)
{
	t_chunk		*chunk;
	size_t		size;
	unsigned	*n;

	// setup
	p = pool_init(&pool, sizeof(unsigned));
	size = ROUND_UP_8(sizeof(unsigned));

	// tests
	v_assert_size_t(size, ==, p->elem_size);
	v_assert_size_t(511, ==, p->chunk_capacity);
	v_assert_ptr(NULL, !=, p->free_list);
	v_assert_ptr(NULL, !=, p->chunks_list);

	// linkage interne
	uintptr_t	*pValue = p->free_list;
	char		*pAddr = (char*)&p->chunks_list->head;
	while (*pValue)
	{
		v_assert_ptr(pAddr, ==, pValue);
		pAddr += p->elem_size;
		v_assert_uintptr(*pValue, ==, pAddr);
		pValue += 1;
	}
	v_assert_uintptr(0, ==, *pValue);

	// freelist
	v_assert_ptr(NULL, !=, p->free_list);
	n = p->free_list;
	*n = ~0U;

	teardown();
	VTS;
}

static void	test_02_pool_init_SizeOfArbitraryStruct(void)
{
	t_chunk		*chunk;
	size_t		size;
	unsigned	*n;

	struct s_pool_test
	{
		void	*p[3];
		int		i[1];
		char	c[1];
	} t;

	// setup
	p = pool_init(&pool, sizeof(struct s_pool_test));
	size = ROUND_UP_8(sizeof(struct s_pool_test));

	// tests
	v_assert_size_t(size, ==, p->elem_size);
	v_assert_size_t(127, ==, p->chunk_capacity);
	v_assert_ptr(NULL, !=, p->free_list);
	v_assert_ptr(NULL, !=, p->chunks_list);

	// linkage interne
	uintptr_t	*pValue = p->free_list;
	char		*pAddr = (char*)&p->chunks_list->head;

	while (*pValue)
	{
		v_assert_ptr(pAddr, ==, pValue);
		pAddr += p->elem_size;
		v_assert_uintptr(*pValue, ==, pAddr);
		pValue += p->elem_size / 8;
	}
	v_assert_uintptr(0, ==, *pValue);

	// freelist
	v_assert_ptr(NULL, !=, p->free_list);
	n = p->free_list;
	*n = ~0U;

	teardown();
	VTS;
}

void	suite_pool_init(void)
{
	test_00_pool_init_ArgEqualZero();
	test_01_pool_init_SizeOfInt();
	test_02_pool_init_SizeOfArbitraryStruct();

	VSS;
}
