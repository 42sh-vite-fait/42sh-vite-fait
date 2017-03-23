/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strndup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubois <adubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 13:15:24 by adubois           #+#    #+#             */
/*   Updated: 2016/05/26 13:18:55 by adubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	test_00_strndup_EmptyString(void)
{
	char	str[] = "";
	char	*res1;
	char	*res2;

	res1 = ft_strndup(str, 42);
	res2 = strndup(str, 42);
	v_assert_str(res1, res2);
	free(res1);
	free(res2);

	VTS;
}

static void	test_01_strndup_SimpleString(void)
{
	char	str[] = "Hello World!";
	char	*res1;
	char	*res2;

	res1 = ft_strndup(str, 42);
	res2 = strndup(str, 42);
	v_assert_str(res1, res2);
	free(res1);
	free(res2);

	VTS;
}

static void	test_02_strndup_LongString(void)
{
	char	str[] = "iNVIVSvRyzGZuqmQo66i FjJZMkeSqQlmFVOsF1by "
					"7W4tCo99aiyrLxOggDp5 E9fN4ckgMUEs1sXvxEPn "
					"DQfAGv7N3wOJVN39hcFB PYv4inlqKOez87HVzR70 "
					"199CZPuWfYAkXhehQkU1 6Hz1QcC72HJSygDsFLHX "
					"hBbfUW4RY5FCeaXZwPPd jUus5zmEwkoh1FwCxUN3";
	char	*res1;
	char	*res2;

	res1 = ft_strndup(str, 4242);
	res2 = strndup(str, 4242);
	v_assert_str(res1, res2);
	free(res1);
	free(res2);

	VTS;
}

static void	test_03_strndup_LongStringLowerN(void)
{
	char	str[] = "iNVIVSvRyzGZuqmQo66i FjJZMkeSqQlmFVOsF1by "
					"7W4tCo99aiyrLxOggDp5 E9fN4ckgMUEs1sXvxEPn "
					"DQfAGv7N3wOJVN39hcFB PYv4inlqKOez87HVzR70 "
					"199CZPuWfYAkXhehQkU1 6Hz1QcC72HJSygDsFLHX "
					"hBbfUW4RY5FCeaXZwPPd jUus5zmEwkoh1FwCxUN3";
	char	*res1;
	char	*res2;

	res1 = ft_strndup(str, 42);
	res2 = strndup(str, 42);
	v_assert_str(res1, res2);
	free(res1);
	free(res2);

	VTS;
}

static void	test_04_strndup_SimpleStringN0(void)
{
	char	str[] = "Hello World!";
	char	*res1;
	char	*res2;

	res1 = ft_strndup(str, 0);
	res2 = strndup(str, 0);
	v_assert_str(res1, res2);
	free(res1);
	free(res2);

	VTS;
}

void		suite_strndup(void)
{
	test_00_strndup_EmptyString();
	test_01_strndup_SimpleString();
	test_02_strndup_LongString();
	test_03_strndup_LongStringLowerN();
	test_04_strndup_SimpleStringN0();

	VSS;
}
