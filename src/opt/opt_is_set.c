/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_is_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:24:06 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:32:56 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "opt.h"

extern unsigned	g_opt_shell;

bool	opt_is_set(unsigned opt)
{
	return (g_opt_shell & opt);
}
