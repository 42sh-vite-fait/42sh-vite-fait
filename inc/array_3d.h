/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 17:00:12 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 17:00:17 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_3D_H
# define ARRAY_3D_H

# include <stdint.h>

/*
** A 3D array encapsulation.
*/

# define X(A) (sizeof(**(A)) / sizeof(***(A)))
# define Y(A) (sizeof(*(A)) / sizeof(**(A)))
# define Z(A) (sizeof(A) / sizeof(*(A)))

# define CREATE_ARRAY_3D(A) (t_3d_array){ (A), X(A), Y(A), Z(A), {0}}

# define ARRAY_3D_TYPE(A, T) const T (*)[(A).size_y][(A).size_x]
# define ARRAY_3D_AT(A, T, X, Y, Z) ((ARRAY_3D_TYPE(A, T))(A).data)[Z][Y][X]

typedef struct s_3d_array		t_3d_array;

struct	s_3d_array
{
	const void	*data;
	uint32_t	size_x;
	uint32_t	size_y;
	uint32_t	size_z;
	uint8_t		pad[4];
};

#endif
