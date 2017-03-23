/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_clone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:38:32 by crenault          #+#    #+#             */
/*   Updated: 2016/11/08 15:49:02 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_42.h"

t_string	*string_clone(t_string *dst, const t_string *src)
{
	return (string_init_ndup(dst, src->str, src->len));
}
