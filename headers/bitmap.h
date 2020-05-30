/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 03:22:32 by bbellavi          #+#    #+#             */
/*   Updated: 2020/05/30 08:36:20 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMAP_H
# define BITMAP_H

#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

typedef struct	s_vec
{
	int	x;
	int y;
}				t_vec;

typedef struct	s_image
{
	char			*filename;
	int				width;
	int				height;
	int				bpp;
	int				size_line;
	int				endian;
	void			*img_ptr;
	unsigned int	*addr;
}				t_image;

typedef struct	s_infos
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	image;
}				t_infos;

typedef struct	s_bitmap
{
	char		bf_type[2];
	uint32_t	bf_size;
	uint32_t	bf_reserved;
	uint32_t	bf_offset_bits;

	uint32_t	bi_size;
	uint32_t	bi_width;
	uint32_t	bi_height;
	u_int16_t	bi_planes;
	u_int16_t	bi_bit_count;
	uint32_t	bi_compression;
	uint32_t	bi_size_image;
	uint32_t	bi_x_ppm;
	uint32_t	bi_y_ppm;
	uint32_t	bi_clr_used;
	uint32_t	bi_clr_important;
}				t_bitmap;

# define R_MASK 0xff0000
# define G_MASK 0x00ff00
# define B_MASK 0x0000ff

#endif