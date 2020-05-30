/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 03:21:39 by bbellavi          #+#    #+#             */
/*   Updated: 2020/05/31 00:11:42 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx/mlx.h"
#include <string.h>
#include "bitmap.h"

# define BMP_IMAGE_HEADER_SIZE 40
# define BMP_FILES_HEADER_SIZE 14
# define BITS_PER_PIXEL 8
# define MAGIC_VALUE 0x4d42

t_bitmap	create_bitmap(t_vec res)
{
	t_bitmap bitmap;

	bitmap = (t_bitmap){
		.bf_type = MAGIC_VALUE,
		.bf_size = res.x * res.y + BMP_IMAGE_HEADER_SIZE + BMP_FILES_HEADER_SIZE,
		.bf_reserved1 = 0,
		.bf_reserved2 = 0,
		.bf_offset_bits = 54,
		.bi_size = BMP_IMAGE_HEADER_SIZE,
		.bi_width = res.x,
		.bi_height = res.y,
		.bi_planes = 1,
		.bi_bit_count = 32,
		.bi_compression = 0,
		.bi_size_image = res.x * res.y * 3,
		.bi_x_ppm = 0,
		.bi_y_ppm = 0,
		.bi_clr_used = 0,
		.bi_clr_important = 0
	};
	return (bitmap);
}

int		export_to_bmp(const char *filename, t_infos *infos)
{
	const int		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0777);
	const t_bitmap	bmp = create_bitmap((t_vec){infos->image.width, infos->image.height});
	int				y;

	if (fd < 0)
		return (1);
	write(fd, &bmp, sizeof(bmp));
	y = 0;
	while (y < infos->image.height)
	{
		unsigned int *line = &infos->image.addr[(infos->image.height - y - 1) * infos->image.width];
		write(fd, line, sizeof(unsigned int) * infos->image.width);
		y++;
	}
	close(fd);
	return (0);
}

int		ends_with(char *s, const char *ext)
{
	const size_t ssize = strlen(s);
	const size_t ext_size = strlen(ext);

	if (ssize < strlen(ext))
		return (0);
	s = &s[ssize - ext_size];
	if (strncmp(s, ext, ext_size) == 0)
		return (1);
	return (0);
}

int		main(int argc, char **argv)
{
	t_infos infos;

	if (argc > 2)
	{
		if (ends_with(argv[1], XPM_EXT) && ends_with(argv[2], BMP_EXT))
		{
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
			export_to_bmp(argv[2], &infos);
		}
		else
		{
			printf("Bad extension\n");
		}
	}
	else
	{
		printf("Usage : ./main src.xpm target.bmp\n");
		printf("This program convert xpm file to bmp.\n");
	}
	return (0);
}