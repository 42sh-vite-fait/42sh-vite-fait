/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnlen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubois <adubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 12:39:48 by adubois           #+#    #+#             */
/*   Updated: 2016/05/26 12:46:01 by adubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	test_00_strnlen_EmptyString(void)
{
	char	str[] = "";

	v_assert_uint(ft_strnlen(str, 42), ==, strnlen(str, 42));

	VTS;
}

static void	test_01_strnlen_SimpleString(void)
{
	char	str[] = "Hello World!";

	v_assert_uint(ft_strnlen(str, 42), ==, strnlen(str, 42));

	VTS;
}

static void	test_02_strnlen_LongString(void)
{
	char	str[] = "iNVIVSvRyzGZuqmQo66i FjJZMkeSqQlmFVOsF1by "
					"7W4tCo99aiyrLxOggDp5 E9fN4ckgMUEs1sXvxEPn "
					"DQfAGv7N3wOJVN39hcFB PYv4inlqKOez87HVzR70 "
					"199CZPuWfYAkXhehQkU1 6Hz1QcC72HJSygDsFLHX "
					"hBbfUW4RY5FCeaXZwPPd jUus5zmEwkoh1FwCxUN3";

	v_assert_uint(ft_strnlen(str, 4242), ==, strnlen(str, 4242));

	VTS;
}

static void	test_03_strnlen_LongStringLowerN(void)
{
	char	str[] = "iNVIVSvRyzGZuqmQo66i FjJZMkeSqQlmFVOsF1by "
					"7W4tCo99aiyrLxOggDp5 E9fN4ckgMUEs1sXvxEPn "
					"DQfAGv7N3wOJVN39hcFB PYv4inlqKOez87HVzR70 "
					"199CZPuWfYAkXhehQkU1 6Hz1QcC72HJSygDsFLHX "
					"hBbfUW4RY5FCeaXZwPPd jUus5zmEwkoh1FwCxUN3";

	v_assert_uint(ft_strnlen(str, 42), ==, strnlen(str, 42));

	VTS;
}

static void	test_04_strnlen_SimpleStringN0(void)
{
	char	str[] = "Hello World!";

	v_assert_uint(ft_strnlen(str, 0), ==, strnlen(str, 0));

	VTS;
}

void		suite_strnlen(void)
{
	test_00_strnlen_EmptyString();
	test_01_strnlen_SimpleString();
	test_02_strnlen_LongString();
	test_03_strnlen_LongStringLowerN();
	test_04_strnlen_SimpleStringN0();

	VSS;
}
