/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubois <adubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 13:02:33 by adubois           #+#    #+#             */
/*   Updated: 2016/05/26 13:06:46 by adubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	test_00_strdup_EmptyString(void)
{
	char	str[] = "";
	char	*res1;
	char	*res2;

	res1 = ft_strdup(str);
	res2 = strdup(str);
	v_assert_str(res1, res2);
	free(res1);
	free(res2);

	VTS;
}

static void	test_01_strdup_SimpleString(void)
{
	char	str[] = "Hello World!";
	char	*res1;
	char	*res2;

	res1 = ft_strdup(str);
	res2 = strdup(str);
	v_assert_str(res1, res2);
	free(res1);
	free(res2);

	VTS;
}

static void	test_02_strdup_LongString(void)
{
	char	str[] = "iNVIVSvRyzGZuqmQo66i FjJZMkeSqQlmFVOsF1by "
					"7W4tCo99aiyrLxOggDp5 E9fN4ckgMUEs1sXvxEPn "
					"DQfAGv7N3wOJVN39hcFB PYv4inlqKOez87HVzR70 "
					"199CZPuWfYAkXhehQkU1 6Hz1QcC72HJSygDsFLHX "
					"hBbfUW4RY5FCeaXZwPPd jUus5zmEwkoh1FwCxUN3";
	char	*res1;
	char	*res2;

	res1 = ft_strdup(str);
	res2 = strdup(str);
	v_assert_str(res1, res2);
	free(res1);
	free(res2);

	VTS;
}

void		suite_strdup(void)
{
	test_00_strdup_EmptyString();
	test_01_strdup_SimpleString();
	test_02_strdup_LongString();

	VSS;
}
