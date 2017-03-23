#include "array_42.h"

t_array	*array_swap(t_array *a, size_t e1, size_t e2)
{
	unsigned char	tmp[a->elem_size];
	void			*elem1;
	void			*elem2;

	if (e1 >= a->len || e2 >= a->len)
		return (NULL);
	elem1 = array_get_at(a, e1);
	elem2 = array_get_at(a, e2);
	ft_memcpy(tmp, elem1, a->elem_size);
	ft_memcpy(elem1, elem2, a->elem_size);
	ft_memcpy(elem2, tmp, a->elem_size);
	return (a);
}
