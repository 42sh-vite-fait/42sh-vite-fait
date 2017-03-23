/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubois <adubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 12:06:09 by adubois           #+#    #+#             */
/*   Updated: 2016/07/26 21:09:01 by leonhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	test_00_strlen_EmptyString(void)
{
	char	*str = "";

	v_assert_size_t(ft_strlen(str), ==, strlen(str));

	VTS;
}

static void	test_01_strlen_SimpleString(void)
{
	char	*str = "Hello World!";

	v_assert_size_t(ft_strlen(str), ==, strlen(str));

	VTS;
}

static void	test_02_strlen_LongString(void)
{
	char	*str = "iNVIVSvRyzGZuqmQo66i FjJZMkeSqQlmFVOsF1by "
					"7W4tCo99aiyrLxOggDp5 E9fN4ckgMUEs1sXvxEPn "
					"DQfAGv7N3wOJVN39hcFB PYv4inlqKOez87HVzR70 "
					"199CZPuWfYAkXhehQkU1 6Hz1QcC72HJSygDsFLHX "
					"hBbfUW4RY5FCeaXZwPPd jUus5zmEwkoh1FwCxUN3";

	v_assert_size_t(ft_strlen(str), ==, strlen(str));

	VTS;
}

void		suite_strlen(void)
{
	test_00_strlen_EmptyString();
	test_01_strlen_SimpleString();
	test_02_strlen_LongString();

	VSS;
}
