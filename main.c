/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 03:21:39 by bbellavi          #+#    #+#             */
/*   Updated: 2020/05/30 15:25:27 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx/mlx.h"
#include <string.h>
#include "bitmap.h"

# define BMP_SIGN "BM"
# define BMP_IMAGE_HEADER_SIZE 40
# define BMP_FILES_HEADER_SIZE 14
# define BITS_PER_PIXEL 8

t_bitmap	create_bitmap(t_vec res)
{
	t_bitmap bitmap;

	bitmap = (t_bitmap){
		.bf_size = res.x * res.y + BMP_IMAGE_HEADER_SIZE + BMP_FILES_HEADER_SIZE,
		.bf_reserved = 0,
		.bf_offset_bits = sizeof(t_bitmap),
		.bi_size = BMP_IMAGE_HEADER_SIZE,
		.bi_width = res.x,
		.bi_height = res.y,
		.bi_planes = 0,
		.bi_bit_count = 32,
		.bi_compression = 0,
		.bi_size_image = res.x * res.y,
		.bi_x_ppm = 0,
		.bi_y_ppm = 0,
		.bi_clr_used = 0,
		.bi_clr_important = 0
	};
	memcpy(&bitmap.bf_type, "BM", 2);
	return (bitmap);
}

/*
	We consider the color table greater than 8.
	No need to include color table.
*/

int		export_to_bmp(const char *filename, t_infos *infos)
{
	const int		fd = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	const t_bitmap	bmp = create_bitmap((t_vec){infos->image.width, infos->image.height});
	t_vec			i;

	printf("%lu\n", sizeof(bmp.bf_type));
	if (fd < 0)
		return (1);
	write(fd, &bmp, sizeof(bmp));
	i.y = 0;
	while (i.y < infos->image.height)
	{
		i.x = 0;
		while (i.x < infos->image.width)
		{
			unsigned int index = (infos->image.width - i.x - 1) + (infos->image.height - i.y - 1) * infos->image.width;
			unsigned int color = infos->image.addr[index];
			unsigned char colors[3];

			colors[0] = color & R_MASK;
			colors[1] = color & G_MASK;
			colors[2] = color & B_MASK;
			printf("sizeof %lu\n", sizeof(colors));
			write(fd, colors, sizeof(color));
			i.x++;
		}
		i.y++;
	}
	close(fd);
	return (0);
}


int		main(void)
{
	t_infos infos;

	infos.mlx_ptr = mlx_init();
	infos.image.filename = "./assets/hitler.xpm";
	infos.image.img_ptr = mlx_xpm_file_to_image(
		infos.mlx_ptr,
		infos.image.filename,
		&infos.image.width,
		&infos.image.height
	);
	infos.image.addr = (unsigned int*)mlx_get_data_addr(
		infos.image.img_ptr,
		&infos.image.bpp,
		&infos.image.size_line,
		&infos.image.endian
	);
	printf("Dimension : %ix%i\n", infos.image.width, infos.image.height);
	export_to_bmp("img.bmp", &infos);
	return (0);
}