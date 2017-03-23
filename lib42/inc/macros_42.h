/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros_42.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 16:28:48 by djean             #+#    #+#             */
/*   Updated: 2016/09/09 16:37:03 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_42_H
# define MACROS_42_H

# define FT_ABS(x)			(((x) < 0) ? -(x) : (x))
# define FT_MAX(a, b)		((a) < (b) ? (b) : (a))
# define FT_MIN(a, b)		((a) > (b) ? (b) : (a))
# define FREE(ptr)			(free(ptr), (ptr) = NULL)
# define ARR_SIZ_MAX(a)		(sizeof(a) / sizeof((a)[0]))
# define IS_POWER_OF_2(n)	((((n) - 1) & (n)) == 0)

#endif
