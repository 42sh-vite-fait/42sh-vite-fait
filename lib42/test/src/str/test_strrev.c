#include "header.h"

static char deep[] = "Are you feeling the true reality of the Truth...";
static char hw[] = "HelloWorld!";
static char nb[] = "0123456789";
static char onlyA[] = "A";

void	test_strrev(void)
{
	v_assert_str(ft_strrev(deep), "...hturT eht fo ytilaer eurt eht gnileef uoy erA");
	v_assert_str(ft_strrev(hw), "!dlroWolleH");
	v_assert_str(ft_strrev(nb), "9876543210");
	v_assert_str(ft_strrev(onlyA), "A");

	v_test_success("Strrev basic");
}

void	suite_strrev(void)
{
	test_strrev();

	v_suite_success("Strrev");
}
