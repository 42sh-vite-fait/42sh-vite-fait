/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_42.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 16:28:49 by djean             #+#    #+#             */
/*   Updated: 2016/10/11 02:00:28 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_42_H
# define STRUCTS_42_H

# include <stdlib.h>

struct	s_chunk
{
	void	*next;
	void	*head;
};

struct	s_pool
{
	struct s_chunk	*chunks_list;
	void			*free_list;
	size_t			chunk_capacity;
	size_t			elem_size;
};

struct	s_string
{
	char	*str;
	size_t	len;
	size_t	capacity;
};

struct	s_array
{
	void		*data;
	size_t		len;
	size_t		capacity;
	size_t		elem_size;
};

struct	s_cbuffer
{
	void		*data;
	size_t		len;
	size_t		capacity;
	size_t		elem_size;
	void		(*delete_func)(void *);
	size_t		start;
	size_t		end;
};

struct	s_format
{
	unsigned int	f_sharp;
	unsigned int	f_zero;
	unsigned int	f_minus;
	unsigned int	f_space;
	unsigned int	f_plus;
	unsigned int	min_width;
	int				prec;
	char			len_mod;
	char			conv;
	char			no_conv;
	char			pad[1];
};

struct	s_gnl
{
	char	*str;
	char	*eol;
	int		fd;
	int		offset;
	int		reads;
	char	pad[4];
};

#endif
